//
// Created by Ivan on 19.11.2020.
//

#include "DateTime.h"
#include <ctime>
#include "JSON.h"

DateTime::DateTime(): BaseDateTime(new tm) {}

DateTime::DateTime(tm *dateTimeInfo) : BaseDateTime(dateTimeInfo) {}

DateTime::DateTime(time_t timestamp, Byte timeZone) : BaseDateTime(timestamp, timeZone) {}

DateTime::DateTime(Byte timeZone) : BaseDateTime(timeZone) {}

Json DateTime::stringify(JSON::JSONOptions &options) {
    string dateTimeString = toString("%FT%X");

    return JSON::stringify(dateTimeString);
}

void DateTime::parse(Json json) {

}

int DateTime::getHours() {
    return dateTimeInfo->tm_hour;
}

int DateTime::getMinutes() {
    return dateTimeInfo->tm_min;
}

int DateTime::getSeconds() {
    return dateTimeInfo->tm_sec;
}

int DateTime::getMilliseconds() {
    return 0;
}

int DateTime::getYear() {
    return dateTimeInfo->tm_year;
}

int DateTime::getFullYear() {
    return 1900 + dateTimeInfo->tm_year;
}

int DateTime::getDay() {
    return dateTimeInfo->tm_mday;
}

int DateTime::getMonth() {
    return dateTimeInfo->tm_mon;
}