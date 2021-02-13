//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_TIME_H
#define WEBX_TIME_H

#include "BaseDateTime.h"
#include "object.h"

class Time : public BaseDateTime {
public:
    Time();

    explicit Time(tm *dateTimeInfo);

    explicit Time(time_t timestamp, Byte timeZone);

    explicit Time(Byte timeZone);

    virtual int getHours();

    virtual int getMinutes();

    virtual int getSeconds();

    virtual int getMilliseconds();

    Json stringify(JSON::JSONOptions &options) override;

    void parse(Json json) override;
};


#endif //WEBX_TIME_H
