//
// Created by Ivan on 19.11.2020.
//

#include "WebServer.h"

#include <utility>
#include "Console.h"
#include "StaticFile.h"

#define ERROR_TEMPLATE "<div style='margin: 20px 30px;'><h1 style='color: red;'>Error ${0}</h1><hr /><h3>Request '<code>${1}</code>' worked with an error!</h3><p>${2}</p></div>"

using namespace Web;

void WebServer::clientHandler(Socket *clientSocket) {
    do {
        auto requestContent = clientSocket->readFull();
        if (requestContent->isEmpty()) {
            break;
        }

        auto httpRequest = new HttpRequest(requestContent);
        auto httpResponse = useWorker(httpRequest);

        if (httpResponse->status >= Http::EResponseStatus::BadRequest) {
            Console::error(string("path: \"${0}\" code: ${1}", {httpRequest->path, httpResponse->status}));
        } else {
            Console::success(string("path: \"${0}\" code: ${1}", {httpRequest->path, httpResponse->status}));
        };

        clientSocket->sendResponse(httpResponse);

        delete httpResponse;
        delete httpRequest;
    } while (settings.isKeepAlive);

    clientSocket->close();

    delete clientSocket;
}

int WebServer::serverHandler(const std::function<void(Socket(*))> &handler) {
    addrinfo *addr;
    WSAData wsaData{};
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        exit(1);
    }

    struct addrinfo tempAddr{};
    ZeroMemory(&tempAddr, sizeof(tempAddr));

    tempAddr.ai_family = AF_INET;
    tempAddr.ai_socktype = SOCK_STREAM;
    tempAddr.ai_protocol = IPPROTO_TCP;
    tempAddr.ai_flags = AI_PASSIVE;

    if (getaddrinfo(settings.host.c_str(), string(settings.port).c_str(), &tempAddr, &addr) != 0) {
        WSACleanup();
    }

    SOCKET SocketListen = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    if (SocketListen == INVALID_SOCKET) {
        Console::writeLine(WSAGetLastError());

        freeaddrinfo(addr);
        WSACleanup();

        return 1;
    }

    if (bind(SocketListen, addr->ai_addr, (int) addr->ai_addrlen) == SOCKET_ERROR) {
        Console::writeLine(WSAGetLastError());

        freeaddrinfo(addr);
        closesocket(SocketListen);
        WSACleanup();

        return 1;
    }

    if (listen(SocketListen, SOMAXCONN) == SOCKET_ERROR) {
        Console::writeLine(WSAGetLastError());

        closesocket(SocketListen);
        WSACleanup();

        return 1;
    }

    Console::success(string("Server started: http://${0}:${1}", {settings.host, settings.port}));

    try {
        while (true) {
            SOCKET socketClient = accept(SocketListen, nullptr, nullptr);

            if (socketClient == -1) {
                break;
            }

            std::thread ClientHandlerThread(handler, new Socket(socketClient));

            ClientHandlerThread.detach();
        }
    }
    catch (const std::exception &exception) {
        Console::writeLine(string("Server Error: ${0}", {exception.what()}));

        return -1;
    }

    closesocket(SocketListen);

    return 0;
}

WebServer::WebServer() {
    try {
        auto[fileContent, type] = StaticFile::getFileContent("./appsettings.json");

        WebServer::settings = JSON::parse<JSON::ServerSettings>(fileContent);
    } catch (const Exception &exception) {
        Console::error(exception.what());
    }
}

int WebServer::run() {
    return serverHandler([this](Socket *clientSocket) {
        clientHandler(clientSocket);
    });
}

void WebServer::use(const std::function<HttpResponse *(HttpRequest *)> &useHandler) {
    useHandlers.push_back(useHandler);
}

HttpResponse *WebServer::useWorker(HttpRequest *request) {
    try {
        for (const auto &useHandler: useHandlers) {
            HttpResponse *tempResponse = useHandler(request);

            if (tempResponse) {
                return tempResponse;
            }
        }
    } catch (Exception &exception) {
        return exceptionHandler(request, exception);
    }

    throw Exception::FileNotFoundException(
            string(ERROR_TEMPLATE, {Http::EResponseStatus::NotFound, request->path, __FUNCTION__}));
}

void WebServer::use(Controller *controller) {
    useHandlers.push_back([controller](HttpRequest *request) {
        ControllerAction *action = controller->findAction(request);

        return action ? (*action)(request) : nullptr;
    });
}

void WebServer::useStaticFile(const string &rootPath) {
    useHandlers.push_back([rootPath](HttpRequest *request) {
        const auto path = string("${0}${1}", {rootPath, request->path});

        return StaticFile::getStaticFile(path);
    });
}

void WebServer::use(const list<Controller *> &controllers) {
    for (auto controller: controllers) {
        WebServer::use(controller);
    }
}

int WebServer::run(const std::function<void(Socket *)> &handler) {
    return serverHandler(handler);
}

void WebServer::useExceptionHandler(const std::function<void(HttpResponse *, const Exception &)> &handler) {
    externalExceptionHandler = handler;
}

HttpResponse *WebServer::exceptionHandler(HttpRequest *request, Exception exception) {
    auto response = new HttpResponse;

    response->status = (Http::EResponseStatus) exception.errorCode();
    response->contentType = Http::EContentType::Html;
    response->content = string(ERROR_TEMPLATE, {response->status, request->href, exception.what()});

    if (externalExceptionHandler) {
        externalExceptionHandler(response, exception);
    }

    return response;
}
