//
// Created by Ivan on 19.11.2020.
//

#include "Query.h"
#include "vector.h"

StringObject Query::parse(string query) {
    StringObject result;
    const vector<string> parsedQuery = query.split("&");

    for (string item: parsedQuery) {
        auto parsedItem = item.split("=");
        result[parsedItem[0]] = parsedItem[1];
    }

    return result;
}
