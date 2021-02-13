//
// Created by Ivan on 18.11.2020.
//

#ifndef WEBX_JSON_H
#define WEBX_JSON_H

#include "string.h"
#include "object.h"
#include <functional>
#include <utility>
#include "JSONOptions.h"

namespace JSON {
    Json stringify(string &data);

    Json stringify(string *data);

    Json stringify(int &data);

    Json stringify(int *data);

    Json stringify(float &data);

    Json stringify(float *data);

    Json stringify(double &data);

    Json stringify(double *data);

    Json stringify(Long &data);

    Json stringify(Long *data);

    Json stringify(bool &data);

    Json stringify(bool *data);

    Json stringify(object *data, JSONOptions options = JSONOptions());

    Json stringify(object &data, JSONOptions options = JSONOptions());

    Json stringify(void *data);

    template<class TValue>
    static TValue parse(string json) {
        auto *data = new TValue();
        parse(data, json);

        return *data;
    }

    void parse(int *distItem, string &json);

    void parse(double *distItem, string &json);

    void parse(bool *distItem, string &json);

    void parse(Long *distItem, string &json);

    void parse(string *distItem, string &json);

    void parse(object *distItem, string &json);

    void parse(void *distItem, string &json);
}

#endif //WEBX_JSON_H
