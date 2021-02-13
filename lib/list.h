//
// Created by Ivan on 18.11.2020.
//

#ifndef WEBX_LIST_H
#define WEBX_LIST_H

#include <list>
#include "string.h"
#include "object.h"
#include "JSON.h"
#include "StringifyEngine.h"
#include "ParseEngine.h"
#include "JSONOptions.h"

template<typename TValue, typename Alloc = std::allocator<TValue>>
class list : public std::list<TValue, Alloc>, public object {
public:
    list();

    list(std::initializer_list<TValue> items);

    explicit list(std::list<TValue> items);

    string stringify(JSON::JSONOptions &options) override;

    void parse(string json) override;
};

template<typename TValue, typename Alloc>
string list<TValue, Alloc>::stringify(JSON::JSONOptions &options) {
    JSON::StringifyEngine engine(options);

    for (TValue item: *this) {
        engine.addItem(JSON::stringify(&item));
    }

    return engine.getJsonArray();
}

template<typename TValue, typename Alloc>
list<TValue, Alloc>::list(): std::list<TValue>() {}

template<typename TValue, typename Alloc>
list<TValue, Alloc>::list(const std::initializer_list<TValue> items): std::list<TValue>(items) {}

template<typename TValue, typename Alloc>
list<TValue, Alloc>::list(std::list<TValue> items): std::list<TValue>(items) {}

template<typename TValue, typename Alloc>
void list<TValue, Alloc>::parse(string json) {
    JSON::ParseEngine engine;

    auto context = this;

    engine.parseArray(std::move(json), [context](Json value) {
        auto item = JSON::parse<TValue>(value);

        context->push_back(*item);
    });
}


#endif //WEBX_LIST_H
