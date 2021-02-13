//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_WEBSERVER_H
#define WEBX_WEBSERVER_H

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "ServerSettings.h"
#include "Socket.h"
#include "Controller.h"
#include <list>
#include "Exception.h"

#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <Windows.h>

namespace Web {
    class WebServer {
    private:
        list<std::function<HttpResponse *(HttpRequest *)>> useHandlers;
        std::function<void(HttpResponse *, const Exception &)> externalExceptionHandler = nullptr;
        JSON::ServerSettings settings;

        void clientHandler(Socket *clientSocket);

        int serverHandler(const std::function<void(Socket(*))> &handler);

        HttpResponse *useWorker(HttpRequest *request);

        void useExceptionHandler(const std::function<void(HttpResponse *, const Exception &)> &handler);

    public:
        WebServer();

        void use(const std::function<HttpResponse *(HttpRequest *)> &useHandler);

        void use(Controller *controller);

        void use(const list<Controller *> &controllers);

        void useStaticFile(const string &rootPath = "./static");

        HttpResponse *exceptionHandler(HttpRequest *request, const Exception &exception);

        int run();

        int run(const std::function<void(Socket(*))> &handler);
    };
}


#endif //WEBX_WEBSERVER_H
