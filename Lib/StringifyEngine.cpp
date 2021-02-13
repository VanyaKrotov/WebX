//
// Created by Ivan on 19.11.2020.
//

#include "StringifyEngine.h"

JSON::StringifyEngine::StringifyEngine(JSON::JSONOptions &options) {
    firstSpace = string(" ") * options.spaceCount;
    itemSpace = options.spaceCount > 0 ? "\n" : "";
}

void JSON::StringifyEngine::addItem(const string &item) {
    resultJson.append(string("${1}${0}, ${2}", {item, firstSpace, itemSpace}));
}

string JSON::StringifyEngine::getJsonArray() {
    deleteLastComa();

    return string("[${1}${0}]", {resultJson, itemSpace});
}

string JSON::StringifyEngine::getJsonObject() {
    deleteLastComa();

    return string("{${1}${0}}", {resultJson, itemSpace});
}

void JSON::StringifyEngine::addItem(const string &key, const string &value) {
    resultJson.append(string("${3}\"${0}\": ${1}, ${2}", {
            key, value, itemSpace, firstSpace}));
}

void JSON::StringifyEngine::deleteLastComa() {
    const int commaIndex = resultJson.find_last_of(",");

    if (commaIndex != -1) {
        resultJson.erase(commaIndex, 2);
    }
}