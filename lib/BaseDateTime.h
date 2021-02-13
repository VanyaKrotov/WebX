//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_BASEDATETIME_H
#define WEBX_BASEDATETIME_H

#include <ctime>
#include "string.h"
#include "object.h"

enum ETimeZone {
    UTC,
    CURRENT
};

class BaseDateTime : public object {
protected:
    tm *dateTimeInfo{};
public:
    explicit BaseDateTime(tm *dateTimeInfo);

    explicit BaseDateTime(Byte timeZone = ETimeZone::UTC);

    explicit BaseDateTime(time_t timestamp, Byte timeZone = ETimeZone::UTC);

    bool isEmpty();

    virtual string toString(CByteArray Template);
};

#endif //WEBX_BASEDATETIME_H
