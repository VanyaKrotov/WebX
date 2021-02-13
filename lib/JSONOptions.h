//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_JSONOPTIONS_H
#define WEBX_JSONOPTIONS_H

#include <functional>
#include "string.h"

namespace JSON {
    struct JSONOptions {
        short spaceCount = 0;

        std::function<string(string&, string&)> replaceFn = nullptr; //  = [](string& name, string& value){ return ""; };
    };
}


#endif //WEBX_JSONOPTIONS_H
