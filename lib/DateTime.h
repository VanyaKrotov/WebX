//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_DATETIME_H
#define WEBX_DATETIME_H

#include "BaseDateTime.h"

class DateTime : public BaseDateTime {
public:
    DateTime();

    explicit DateTime(tm *dateTimeInfo);

    explicit DateTime(time_t timestamp, Byte timeZone);

    explicit DateTime(Byte timeZone);

    virtual int getHours();

    virtual int getMinutes();

    virtual int getSeconds();

    virtual int getMilliseconds();

    virtual int getYear();

    virtual int getFullYear();

    virtual int getDay();

    virtual int getMonth();

    Json stringify(JSON::JSONOptions &options) override;

    void parse(Json json) override;
};

#endif //WEBX_DATETIME_H
