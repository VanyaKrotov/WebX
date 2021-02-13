//
// Created by Ivan on 19.11.2020.
//

#include "Date.h"
#include "JSON.h"

Date::Date(Byte timeZone) : BaseDateTime(timeZone) {

}

Date::Date(tm *dateTimeInfo) : BaseDateTime(dateTimeInfo) {}

Date::Date() : BaseDateTime(new tm) {}

Date::Date(time_t timestamp, Byte timeZone) : BaseDateTime(timestamp, timeZone) {}

int Date::getYear() {
    return dateTimeInfo->tm_year;
}

int Date::getFullYear() {
    return 1900 + dateTimeInfo->tm_year;
}

int Date::getDay() {
    return dateTimeInfo->tm_mday;
}

int Date::getMonth() {
    return dateTimeInfo->tm_mon;
}

Json Date::stringify(JSON::JSONOptions &options) {
    string dateString = toString("%F");

    return JSON::stringify(dateString);
}

void Date::parse(Json json) {

}

