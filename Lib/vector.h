//
// Created by Ivan on 18.11.2020.
//

#ifndef WEBX_VECTOR_H
#define WEBX_VECTOR_H

#include <vector>
#include "JSON.h"
#include "StringifyEngine.h"
#include "ParseEngine.h"

class object;

template<class TValue>
class vector : public std::vector<TValue>, public object {
public:
    vector();

    vector(const std::initializer_list<TValue> &items);

    string stringify(JSON::JSONOptions &options) override;

    void parse(string json) override;

    size_t length();

    int indexOf(TValue value);
};

template<class TValue>
vector<TValue>::vector(): std::vector<TValue>() {}

template<class TValue>
vector<TValue>::vector(const std::initializer_list<TValue> &items): std::vector<TValue>(items) {}

template<class TValue>
string vector<TValue>::stringify(JSON::JSONOptions &options) {
    JSON::StringifyEngine engine(options);

    for (TValue item: *this) {
        engine.addItem(JSON::stringify(&item));
    }

    return engine.getJsonArray();
}

template<class TValue>
void vector<TValue>::parse(string json) {
    JSON::ParseEngine engine;

    auto context = this;

    engine.parseArray(std::move(json), [context](Json value) {
        context->push_back(JSON::parse<TValue>(value));
    });
}

template<class TValue>
size_t vector<TValue>::length() {
    return this->size();
}

template<class TValue>
int vector<TValue>::indexOf(TValue value) {
    int index = 0;

    for (auto &item: *this) {
        if (value == item) {
            return index;
        }

        index++;
    }

    return -1;
}

#endif //WEBX_VECTOR_H
