//
// Created by Ivan on 20.11.2020.
//

#ifndef WEBX_ROUTE_H
#define WEBX_ROUTE_H

#include <algorithm>
#include <regex>
#include "dictionary.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "vector.h"


namespace Web {
    typedef std::function<HttpResponse *(HttpRequest *)> ControllerAction;

    enum EParamType {
        Number,
        String
    };

    struct RouteParam {
        size_t start;
        string name;
        EParamType type;

        static EParamType detectType(const string &typeString) {
            if (typeString.find("number") != -1) {
                return EParamType::Number;
            }

            return EParamType::String;
        }

        static bool checkAccessType(string value, EParamType &type) {
            if (type == EParamType::String && !value.empty()) {
                return true;
            }

            return value.regexSearch(R"(^-*[\d.]+$)");
        }
    };

    class Route {
    private:
        string route;
        std::regex *regexForCheck;
        ControllerAction action;
        EHttpType method;
        vector<RouteParam> paramsMap;

        explicit Route(const string &route);

    public:
        Route(const string &route, const ControllerAction &action, const EHttpType &method);

        static Route *get(const string &route, const ControllerAction &action);

        static Route *post(const string &route, const ControllerAction &action);

        static Route *put(const string &route, const ControllerAction &action);

        static Route *del(const string &route, const ControllerAction &action);

        ControllerAction *findAction(HttpRequest *request, const short &parentPrefixLength = 0);
    };
}

#endif //WEBX_ROUTE_H
