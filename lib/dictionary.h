//
// Created by Ivan on 18.11.2020.
//

#ifndef WEBX_DICTIONARY_H
#define WEBX_DICTIONARY_H

#include <map>
#include "list.h"
#include "object.h"
#include "StringifyEngine.h"
#include "ParseEngine.h"
#include "JSONOptions.h"

template<class TKey, class TValue, class Pr = std::less<TKey>, class Alloc = std::allocator<std::pair<const TKey, TValue>>>
class dictionary : public std::map<TKey, TValue, Pr, Alloc>, public object {
public:
    dictionary();

    dictionary(std::initializer_list<std::pair<const TKey, TValue>> initial);

    explicit dictionary(const std::allocator<std::pair<TKey, TValue>> &initial);

    string stringify(JSON::JSONOptions &options) override;

    void parse(string json) override;

    list<TKey> keys();

    list<TValue> values();

    bool hasKey(const string &key);
};

template<class TKey, class TValue, class Pr, class Alloc>
dictionary<TKey, TValue, Pr, Alloc>::dictionary(): std::map<TKey, TValue>() {}

template<class TKey, class TValue, class Pr, class Alloc>
dictionary<TKey, TValue, Pr, Alloc>::dictionary(std::initializer_list<std::pair<const TKey, TValue>> initial)
        : std::map<TKey, TValue>(initial) {}

template<class TKey, class TValue, class Pr, class Alloc>
dictionary<TKey, TValue, Pr, Alloc>::dictionary(const std::allocator<std::pair<TKey, TValue>> &initial)
        : std::map<TKey, TValue>(initial) {}

template<class TKey, class TValue, class Pr, class Alloc>
string dictionary<TKey, TValue, Pr, Alloc>::stringify(JSON::JSONOptions &options) {
    JSON::StringifyEngine engine(options);

    for (auto&[key, value]: *this) {
        engine.addItem(key, JSON::stringify(&value));
    }

    return engine.getJsonObject();
}

template<class TKey, class TValue, class Pr, class Alloc>
void dictionary<TKey, TValue, Pr, Alloc>::parse(string json) {
    JSON::ParseEngine engine;

    auto context = this;

    engine.parseObject(std::move(json), [&context](string key, Json value) {
        auto parsedKey = JSON::parse<TKey>(key);
        auto parsedValue = JSON::parse<TValue>(value);

        (*context)[*parsedKey] = *parsedValue;
    });
}

template<class TKey, class TValue, class Pr, class Alloc>
list<TKey> dictionary<TKey, TValue, Pr, Alloc>::keys() {
    list<TKey> keys;

    for (auto&[key, value] : *this) {
        keys.push_back(key);
    }

    return keys;
}

template<class TKey, class TValue, class Pr, class Alloc>
list<TValue> dictionary<TKey, TValue, Pr, Alloc>::values() {
    list<TValue> values;

    for (auto&[key, value]: *this) {
        values.push_back(value);
    }

    return values;
}

template<class TKey, class TValue, class Pr, class Alloc>
bool dictionary<TKey, TValue, Pr, Alloc>::hasKey(const string &key) {
    for (auto&[iterKey, _]: *this) {
        if (iterKey == key) {
            return true;
        }
    }

    return false;
}

typedef dictionary<string, string> StringObject;

#endif //WEBX_DICTIONARY_H
