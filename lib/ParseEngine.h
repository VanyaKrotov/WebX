//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_PARSEENGINE_H
#define WEBX_PARSEENGINE_H

#include "types.h"
#include <functional>

namespace JSON {
    #define OPEN_BRACKET_OBJECT '{'
    #define CLOSE_BRACKET_OBJECT '}'
    #define OPEN_BRACKET_ARRAY '['
    #define CLOSE_BRACKET_ARRAY ']'


    class ParseEngine {
    public:
        virtual void parseObject(Json json, const std::function<void(string key, Json value)>& returnFn);
        virtual void parseArray(Json json, const std::function<void(Json item)>& returnFn);
    };
}

#endif //WEBX_PARSEENGINE_H
