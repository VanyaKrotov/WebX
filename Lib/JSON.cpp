//
// Created by Ivan on 18.11.2020.
//

#include "JSON.h"

string JSON::stringify(string &data) {
    return string("\"${0}\"", {data});
}

string JSON::stringify(string *data) {
    return data ? stringify(*data) : "null";
}

string JSON::stringify(int &data) {
    return data;
}

string JSON::stringify(int *data) {
    return data ? stringify(*data) : "null";
}

string JSON::stringify(float &data) {
    return data;
}

string JSON::stringify(float *data) {
    return data ? stringify(*data) : "null";
}

string JSON::stringify(double &data) {
    return data;
}

string JSON::stringify(double *data) {
    return data ? stringify(*data) : "null";
}

string JSON::stringify(Long &data) {
    return data;
}

Json JSON::stringify(Long *data) {
    return data ? stringify(*data) : "null";
}

Json JSON::stringify(bool &data) {
    return data ? "true" : "false";
}

Json JSON::stringify(bool *data) {
    return data ? stringify(*data) : "null";
}

Json JSON::stringify(void *data) {
    return "null";
}

Json JSON::stringify(object *data, JSONOptions options) {
    return data ? data->stringify(options) : "null";
}

Json JSON::stringify(object &data, JSONOptions options) {
    return data.stringify(options);
}

void JSON::parse(int *distItem, string &json) {
    *distItem = json.toInt();
}

void JSON::parse(double *distItem, string &json) {
    *distItem = json.toDouble();
}

void JSON::parse(bool *distItem, string &json) {
    *distItem = json.toBool();
}

void JSON::parse(Long *distItem, string &json) {
    *distItem = json.toLong();
}

void JSON::parse(string *distItem, string &json) {
    const int firstBreak = json.find_first_of("\"");

    *distItem = json.substr(firstBreak + 1, json.find_last_of("\"") - firstBreak - 1);
}

void JSON::parse(object *distItem, string &json) {
    distItem->parse(json);
}

void JSON::parse(void *distItem, string &json) {

}


