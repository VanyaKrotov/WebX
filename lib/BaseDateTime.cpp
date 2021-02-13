//
// Created by Ivan on 19.11.2020.
//

#include "BaseDateTime.h"
#include <ctime>

BaseDateTime::BaseDateTime(tm *dateTimeInfo) {
    BaseDateTime::dateTimeInfo = dateTimeInfo;

    const time_t currentTime = time(nullptr);

    gmtime_s(dateTimeInfo, &currentTime);
}

BaseDateTime::BaseDateTime(time_t timestamp, Byte timeZone) : BaseDateTime(new tm) {
    if (timeZone == ETimeZone::CURRENT) {
        localtime_s(dateTimeInfo, &timestamp);
    } else {
        gmtime_s(dateTimeInfo, &timestamp);
    }
}

BaseDateTime::BaseDateTime(Byte timeZone) : BaseDateTime(time(nullptr), timeZone) {}

string BaseDateTime::toString(CByteArray Template) {
    auto buffer = new char[100];

    strftime(buffer, 100, Template, dateTimeInfo);

    string result = buffer;

    delete[] buffer;

    return result;
}

bool BaseDateTime::isEmpty() {
    return dateTimeInfo == nullptr;
}

