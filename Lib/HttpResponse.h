//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_HTTPRESPONSE_H
#define WEBX_HTTPRESPONSE_H

#include "string.h"
#include "dictionary.h"
#include "Cookie.h"
#include "list.h"
#include "ECharset.h"
#include "EContentType.h"
#include "EResponseStatus.h"

namespace Web {
    class HttpResponse {
    public:
        Http::EResponseStatus status = Http::EResponseStatus::Ok;
        list<Cookie> cookies;
        string content;
        ECharset charset = ECharset::WINDOWS_1251;
        Http::EContentType contentType = Http::EContentType::Html;
        string version = "HTTP/1.1";
        StringObject headers;

        string *pack();

        HttpResponse();

        explicit HttpResponse(object &content);

        explicit HttpResponse(const string &content);

        HttpResponse *setCookie(const Cookie &cookie);

        static HttpResponse *fileResponse(const string &content, const Http::EContentType &contentType);

        static string getContentType(const Http::EContentType &contentType);

        static string getCharsetName(const ECharset &charset);

        static HttpResponse *ok(const string &content);

        static HttpResponse *ok(object &content);

        static HttpResponse *ok(const object &content);

        static HttpResponse *notFound(object &content);

        static HttpResponse *notFound(const string &content);

        static HttpResponse *badRequest(object &content);

        static HttpResponse *badRequest(const string &content);

        static HttpResponse *serverError(object &content);

        static HttpResponse *serverError(const string &content);

        static HttpResponse *redirect(const string& location);

    };
}

#endif //WEBX_HTTPRESPONSE_H
