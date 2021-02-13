//
// Created by Ivan on 20.11.2020.
//

#include "Route.h"

using namespace Web;

Route::Route(const string &route, const ControllerAction &action, const EHttpType &method) : Route(route) {
    Route::action = action;
    Route::method = method;
}

Route *Route::get(const string &route, const ControllerAction &action) {
    return new Route(route, action, EHttpType::GET);
}

Route *Route::post(const string &route, const ControllerAction &action) {
    return new Route(route, action, EHttpType::POST);
}

Route *Route::put(const string &route, const ControllerAction &action) {
    return new Route(route, action, EHttpType::PUT);
}

Route *Route::del(const string &route, const ControllerAction &action) {
    return new Route(route, action, EHttpType::DEL);
}

ControllerAction *Route::findAction(HttpRequest *request, const short &parentPrefixLength) {
    if (method != request->httpType) {
        return nullptr;
    }

    const string parsedPath = request->path.substr(parentPrefixLength);
    if (!paramsMap.empty() && std::regex_search(parsedPath, *regexForCheck)) {
        size_t offset = 0;
        size_t end;

        for (auto &param: paramsMap) {
            const size_t start = offset + param.start;

            end = parsedPath.find('/', start + 1);
            const string value = parsedPath.substr(start, end - start);

            offset += value.length();

            if (!RouteParam::checkAccessType(value, param.type)) {
                return nullptr;
            }

            request->query[param.name] = value;
        }
    } else if (parsedPath != route) {
        return nullptr;
    }

    return &action;
}

Route::Route(const string &route) {
    int index = 0;
    size_t offset = 0;
    string regexTemplate = string("^${0}$", {route});
    while ((index = route.find('{', index)) != -1) {
        const size_t separateIndex = route.find(':', index + 1);
        const EParamType type = RouteParam::detectType(route.substr(index + 1, separateIndex - index - 1));
        const size_t end = route.find('}', separateIndex + 1);
        const string paramName = route.substr(separateIndex + 1, end - separateIndex - 1);
        const size_t index_ = regexTemplate.find('{');

        regexTemplate.replace(index_, end - index + 1, EParamType::Number == type ? R"([-\d.]+)" : R"([\w\s]*)");

        paramsMap.push_back({index - offset, paramName, type});

        offset += end - index + 1;
        index = end;
    }

    regexForCheck = new std::regex(regexTemplate);

    Route::route = route;
}
