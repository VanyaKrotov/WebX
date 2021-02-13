//
// Created by Ivan on 18.11.2020.
//

#ifndef WEBX_STRING_H
#define WEBX_STRING_H

#include <string>
#include "types.h"

template<class TValue>
class vector;

class string : public std::string {
public:
    string();

    string(CByteArray value);

    string(ByteArray value);

    string(int value);

    string(double value);

    string(float value);

    string(Long value);

    string(bool value);

    string(DLong value);

    string(std::string value);

    string(Byte value);

    string(string templateString, std::initializer_list<string> items);

    bool isEmpty();

    double toDouble();

    bool toBool();

    Long toLong();

    int toInt();

    bool regexSearch(const string &regexString);

    string trim();

    vector<string> split(const string &separator);

    string operator*(int count);
};


#endif //WEBX_STRING_H
