//
// Created by Ivan on 12.02.2021.
//

#include "Exception.h"
#include "EResponseStatus.h"


Exception::Exception() : std::exception() {
    code = 0;
}

Exception::Exception(const string &message, const int &code) : std::exception(message.c_str()) {
    Exception::code = code;
}

int Exception::errorCode() {
    return code;
}

Exception Exception::FileNotFoundException(const string &message) {
    return Exception(message, Web::Http::EResponseStatus::NotFound);
}

Exception Exception::ArgumentException(const string &message) {
    return Exception(message, Web::Http::EResponseStatus::NotAcceptable);
}
