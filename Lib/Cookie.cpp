//
// Created by Ivan on 19.11.2020.
//

#include "Cookie.h"
#include "vector.h"

Cookie::Cookie() {
    maxAge = 0;
    domain = "";
    path = "/";
    secure = false;
    httpOnly = false;
//	sameSite = defaultSameSite;
}

StringObject Cookie::parse(string &cookieString) {
    StringObject cookies;

    auto parsedCookie = cookieString.split("; ");

    for (const string &item : parsedCookie) {
        const int SeparatorIndex = item.find_first_of('=');
        string Name = item.substr(0, SeparatorIndex);
        string Value = item.substr(SeparatorIndex + 1, item.length() - SeparatorIndex);

        cookies[Name] = Value;
    }

    return cookies;
}

Cookie::Cookie(string name, string value) : Cookie() {
    Cookie::name = name;
    Cookie::value = value;
}

Cookie::Cookie(string name, string value, DateTime expires) :
        Cookie(name, value) {
    Cookie::expires = expires;
}

Cookie::Cookie(string name, string value, DateTime expires, int maxAge) :
        Cookie(name, value, expires) {
    Cookie::maxAge = maxAge;
}

Cookie::Cookie(string name, string value, DateTime expires, int maxAge, string domain) :
        Cookie(name, value, expires, maxAge) {
    Cookie::domain = domain;
}

Cookie::Cookie(string name, string value, DateTime expires, int maxAge, string domain, string path) :
        Cookie(name, value, expires, maxAge, domain) {
    Cookie::path = path;
}

Cookie::Cookie(string name, string value, DateTime expires, int maxAge, string domain, string path, bool secure) :
        Cookie(name, value, expires, maxAge, domain, path) {
    Cookie::secure = secure;
}

Cookie::Cookie(string name, string value, DateTime expires, int maxAge, string domain, string path, bool secure,
               bool httpOnly) :
        Cookie(name, value, expires, maxAge, domain, path, secure) {
    Cookie::httpOnly = httpOnly;
}

Cookie::Cookie(string name, string value, DateTime expires, int maxAge, string domain, string path, bool secure,
               bool httpOnly, short sameSite) :
        Cookie(name, value, expires, maxAge, domain, path, secure, httpOnly) {
    Cookie::sameSite = sameSite;
}

string Cookie::toString() {
    string result = string("${0}=${1}; ", {name, value});

    if (expires.isEmpty()) {
        result += string("Expires=${0}; ", {expires.toString("%a, %d %b %Y %X GMT")});
    }

    if (!domain.isEmpty()) {
        result += string("Domain=${0}; ", {domain});
    }

    if (!path.isEmpty()) {
        result += string("Path=${0}; ", {path});
    }

    if (secure) {
        result += "Secure; ";
    }

    if (httpOnly) {
        result += "HttpOnly; ";
    }

    // Result += String("SameSite=${0} ", { SameSite == SameSite::Lax ? "Lax" : SameSite == SameSite::Strict ? "Strict" : "None" });

    return result;
}
