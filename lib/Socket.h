//
// Created by Ivan on 10.02.2021.
//

#ifndef WEBX_SOCKET_H
#define WEBX_SOCKET_H

#include <utility>
#include <winsock2.h>
#include "string.h"
#include "HttpResponse.h"

namespace Web {
    class Socket {
    private:
        SOCKET socket;
    public:
        explicit Socket(const SOCKET &socket);

        ~Socket();

        string *readFull() const;

        bool sendContent(const string &content) const;

        bool sendContent(string *content) const;

        bool sendResponse(HttpResponse *response) const;

        bool close() const;
    };

}


#endif //WEBX_SOCKET_H
