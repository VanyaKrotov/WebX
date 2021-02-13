//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_DATE_H
#define WEBX_DATE_H

#include <ctime>
#include "types.h"
#include "BaseDateTime.h"
#include "object.h"

class Date : public BaseDateTime {
public:
    Date();

    explicit Date(tm *dateTimeInfo);

    explicit Date(time_t timestamp, Byte timeZone);

    explicit Date(Byte timeZone);

    virtual int getYear();

    virtual int getFullYear();

    virtual int getDay();

    virtual int getMonth();

    Json stringify(JSON::JSONOptions &options) override;

    void parse(Json json) override;
};

#endif //WEBX_DATE_H
