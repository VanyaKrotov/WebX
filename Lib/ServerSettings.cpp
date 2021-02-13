//
// Created by Ivan on 19.11.2020.
//

#include "ServerSettings.h"
#include "ObjectField.h"

using namespace JSON;

ServerSettings::ServerSettings() {
    bindField(new ObjectField("host", host));
    bindField(new ObjectField("port", port));
    bindField(new ObjectField("isKeepAlive", isKeepAlive));
    bindField(new ObjectField("prefixPath", prefixPath));
}
