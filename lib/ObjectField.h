//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_OBJECTFIELD_H
#define WEBX_OBJECTFIELD_H

#include "JSON.h"
#include <any>
#include "string.h"
#include "Field.h"
#include <typeinfo>
#include <iostream>

namespace JSON {
    template<class TValue = int>
    class ObjectField : public Field {
    private:
        string name;
        TValue *value;
    public:
        ObjectField(string name, TValue &value);

        void setJson(Json json) override;

        void set(std::any &value) override;

        std::any get() override;

        string toJson() override;

        string getFieldName() override;

        bool isNullable() override;
    };

    template<class TValue>
    void ObjectField<TValue>::setJson(Json json) {
        auto newValue = JSON::parse<TValue>(json);

        *value = *newValue;
    }

    template<class TValue>
    std::any ObjectField<TValue>::get() {
        return *value;
    }

    template<class TValue>
    void ObjectField<TValue>::set(std::any &value) {
        *ObjectField::value = std::any_cast<TValue>(value);
    }

    template<class TValue>
    string ObjectField<TValue>::getFieldName() {
        return name;
    }

    template<class TValue>
    ObjectField<TValue>::ObjectField(string name, TValue &value) {
        ObjectField::value = &value;
        ObjectField::name = name;
    }

    template<class TValue>
    string ObjectField<TValue>::toJson() {
        return JSON::stringify(*value);
    }

    template<class TValue>
    bool ObjectField<TValue>::isNullable() {
        return string(typeid(value).name()).find('*') != -1;
    }
}


#endif //WEBX_OBJECTFIELD_H
