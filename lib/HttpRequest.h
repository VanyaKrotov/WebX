//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_HTTPREQUEST_H
#define WEBX_HTTPREQUEST_H

#include "types.h"
#include "string.h"
#include "dictionary.h"
#include "EHttpType.h"
#include "HttpResponse.h"
#include "Query.h"


namespace Web {
    struct IHttpRequest {
        EHttpType httpType;
        string href;
        string path;
        StringObject headers;
        StringObject cookies;
        StringObject query;

    protected:
        string body;
    };

    class HttpRequest : public IHttpRequest {
    private:
        void requestHeadersParser(const string &request);

        size_t headersParse(const string &request, const size_t &index);

    public:
        explicit HttpRequest(string *request);

        template<class TBody>
        TBody* getDataFromBody();

        static string urlDecode(string &data);

        static string urlEncode(string &data);

        static EHttpType getTypeByName(const string &data);
    };

    template<class TBody>
    TBody* Web::HttpRequest::getDataFromBody() {
        if (headers.hasKey("Content-Type") && headers["Content-Type"].find("application/json") != -1) {
            return JSON::parse<TBody>(body);
        }

        auto bodyQueryObject = Query::parse(HttpRequest::urlDecode(body));

        string json = JSON::stringify(bodyQueryObject);

        return JSON::parse<TBody>(json);
    }

}

#endif //WEBX_HTTPREQUEST_H
