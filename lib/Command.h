//
// Created by Ivan on 24.11.2020.
//

#ifndef WEBX_COMMAND_H
#define WEBX_COMMAND_H

#include "string.h"
#include "vector.h"
#include "dictionary.h"
#include "ECommandType.h"

typedef vector<string> CommandArguments;
typedef dictionary<string, bool> FlagsObject;
typedef dictionary <ByteArray, ByteArray> Props;

struct Command {
    string name;
    CommandArguments arguments;
    std::function<void(Props &props, FlagsObject &flags)> handler = nullptr;
    ByteArray description;
};


#endif //WEBX_COMMAND_H
