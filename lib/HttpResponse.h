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
        ECharset charset = ECharset::UTF_8;
        Http::EContentType contentType = Http::EContentType::Html;
        string version = "HTTP/1.1";
        StringObject headers;

        string *pack();

        HttpResponse();

        explicit HttpResponse(object &content);

        explicit HttpResponse(const string &content);

        explicit HttpResponse(const string &content, const Http::EContentType &contentType);

        explicit HttpResponse(object &content, const Http::EContentType &contentType);

        explicit HttpResponse(const string &content, const Http::EContentType &contentType,
                              const Http::EResponseStatus &status);

        explicit HttpResponse(object &content, const Http::EContentType &contentType,
                              const Http::EResponseStatus &status);

        HttpResponse *setCookie(const Cookie &cookie);

        static HttpResponse *fileResponse(const string &content, const Http::EContentType &contentType);

        static string getContentType(const Http::EContentType &contentType);

        static string getCharsetName(const ECharset &charset);

        static HttpResponse *redirect(const string &location);


    };
}

#endif //WEBX_HTTPRESPONSE_H
