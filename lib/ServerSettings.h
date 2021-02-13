//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_SERVERSETTINGS_H
#define WEBX_SERVERSETTINGS_H

#include "object.h"
#include "dictionary.h"
#include "string"
#include "ObjectField.h"

namespace JSON {
    struct IServerSettings {
        string host = "localhost";
        int port = 8000;
        bool isKeepAlive = false;
        string prefixPath;
    };

    class ServerSettings : public object, public IServerSettings {
    public:
        ServerSettings();
    };
}


#endif //WEBX_SERVERSETTINGS_H
