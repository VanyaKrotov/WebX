//
// Created by Ivan on 18.11.2020.
//

#include "object.h"

#include <utility>
#include "StringifyEngine.h"
#include "ParseEngine.h"
#include "dictionary.h"

string object::stringify(JSON::JSONOptions &options) {
    if (fields.empty()) {
        return "{}";
    }

    JSON::StringifyEngine engine(options);

    for (auto field: fields) {
        engine.addItem(field->getFieldName(), field->toJson());
    }

    return engine.getJsonObject();
}

void object::parse(string json) {
    JSON::ParseEngine engine;
    dictionary<string, JSON::Field *> tempObject;

    for (auto field: fields) {
        tempObject[field->getFieldName()] = field;
    }

    engine.parseObject(std::move(json), [&tempObject](string key, Json value) {
        auto pKey = JSON::parse<string>(std::move(key));
        if (pKey == nullptr || pKey->empty() || !tempObject.hasKey(*pKey)) {
            return;
        }

        tempObject[*pKey]->setJson(std::move(value));
    });
}

void object::bindField(JSON::Field *field) {
    fields.push_back(field);
}
