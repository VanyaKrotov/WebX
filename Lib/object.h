//
// Created by Ivan on 18.11.2020.
//

#ifndef WEBX_OBJECT_H
#define WEBX_OBJECT_H

#include "Field.h"
#include "Exception.h"
#include <vector>

namespace JSON {
    struct JSONOptions;
}

class object {
protected:
    std::vector<JSON::Field *> fields;

    void bindField(JSON::Field *field);

public:
    virtual Json stringify(JSON::JSONOptions &options);

    virtual void parse(Json json);

    template<class TDest>
    TDest *mapTo();
};

template<class TDest>
TDest *object::mapTo() {
    if (!std::is_base_of<object, TDest>::value) {
        throw Exception::ArgumentException(
                string("${0} | The resource item does not have a matching object parent", {__FUNCTION__}));
    }

    auto dest = new TDest();

    JSON::JSONOptions options;

    auto currentJson = stringify(options);

    dest->parse(currentJson);

    return dest;
}

#endif //WEBX_OBJECT_H

