//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_FIELD_H
#define WEBX_FIELD_H

#include "string.h"
#include <any>

namespace JSON {

    class Field {
    public:
        virtual void setJson(Json json) = 0;

        virtual void set(std::any &) = 0;

        virtual std::any get() = 0;

        virtual string toJson() = 0;

        virtual string getFieldName() = 0;

        virtual bool isNullable() = 0;

    };
}

#endif //WEBX_FIELD_H
