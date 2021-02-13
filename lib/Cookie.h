//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_COOKIE_H
#define WEBX_COOKIE_H

#include "string.h"
#include "DateTime.h"
#include "dictionary.h"

class Cookie {
public:
    string name;
    string value;
    DateTime expires;
    long int maxAge;
    string domain;
    string path;
    bool secure;
    bool httpOnly;
    short sameSite;

    Cookie();

    Cookie(string, string);

    Cookie(string, string, DateTime);

    Cookie(string, string, DateTime, int);

    Cookie(string, string, DateTime, int, string);

    Cookie(string, string, DateTime, int, string, string);

    Cookie(string, string, DateTime, int, string, string, bool);

    Cookie(string, string, DateTime, int, string, string, bool, bool);

    Cookie(string, string, DateTime, int, string, string, bool, bool, short);

    string toString();

    static dictionary <string, string> parse(string &cookieString);
};

#endif //WEBX_COOKIE_H
