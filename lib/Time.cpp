//
// Created by Ivan on 19.11.2020.
//

#include "Time.h"
#include <ctime>
#include "JSON.h"

Time::Time() : BaseDateTime(new tm) {}

Time::Time(tm *dateTimeInfo) : BaseDateTime(dateTimeInfo) {}

Time::Time(time_t timestamp, Byte timeZone) : BaseDateTime(timestamp, timeZone) {}

Time::Time(Byte timeZone) : BaseDateTime(timeZone) {}

int Time::getHours() {
    return dateTimeInfo->tm_hour;
}

int Time::getMinutes() {
    return dateTimeInfo->tm_min;
}

int Time::getSeconds() {
    return dateTimeInfo->tm_sec;
}

int Time::getMilliseconds() {
    return 0;
}

Json Time::stringify(JSON::JSONOptions &options) {
    string timeString = toString("%X");

    return JSON::stringify(timeString);
}

void Time::parse(Json json) {

}