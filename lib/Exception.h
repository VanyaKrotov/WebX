//
// Created by Ivan on 12.02.2021.
//

#ifndef WEBX_EXCEPTION_H
#define WEBX_EXCEPTION_H

#include <exception>
#include "string.h"
#include "EResponseStatus.h"


class Exception : public std::exception {
private:
    int code = Web::Http::EResponseStatus::InternalServerError;

public:
    Exception();

    explicit Exception(const string &message, const int &code = 0);

    int errorCode() const;

    static Exception FileNotFoundException(const string &message);

    static Exception ArgumentException(const string &message);
};


#endif //WEBX_EXCEPTION_H
