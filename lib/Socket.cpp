//
// Created by Ivan on 10.02.2021.
//

#include "Socket.h"

#define BUFFER_SIZE 4096

using namespace Web;

Socket::Socket(const SOCKET &socket) {
    this->socket = socket;
}

bool Socket::sendContent(const string &content) const {
    return send(socket, content.c_str(), content.length(), 0) >= 0;
}

bool Socket::sendContent(string *content) const {
    const bool result = send(socket, content->c_str(), content->length(), 0) >= 0;

    delete content;

    return result;
}

string *Socket::readFull() const {
    auto result = new string();

    Byte buffer[BUFFER_SIZE];
    int readCount;
    do {
        readCount = recv(socket, buffer, BUFFER_SIZE, 0);

        if (readCount != 0) {
            buffer[readCount] = '\0';
            result->append(buffer);

        }
    } while (readCount == BUFFER_SIZE);

    return result;
}

bool Socket::close() const {
    return closesocket(socket);
}

Socket::~Socket() {
    close();
}

bool Socket::sendResponse(HttpResponse *response) const {
    auto content = response->pack();

    return sendContent(content);
}
