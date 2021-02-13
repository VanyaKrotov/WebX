//
// Created by Ivan on 19.11.2020.
//

#include "HttpResponse.h"
#include <array>
#include "StaticFile.h"

dictionary<string, std::array<Web::Http::EContentType, 2>> HttpResponseTypes = {
        {"text",        std::array<Web::Http::EContentType, 2>{Web::Http::EContentType::Html,
                                                               Web::Http::EContentType::Css}},
        {"image",       std::array<Web::Http::EContentType, 2>{Web::Http::EContentType::Png,
                                                               Web::Http::EContentType::Bmp}},
        {"application", std::array<Web::Http::EContentType, 2>{Web::Http::EContentType::Json,
                                                               Web::Http::EContentType::SZip}},
        {"video",       std::array<Web::Http::EContentType, 2>{Web::Http::EContentType::Mp4,
                                                               Web::Http::EContentType::Flv}},
        {"audio",       std::array<Web::Http::EContentType, 2>{Web::Http::EContentType::Mp3,
                                                               Web::Http::EContentType::Wav}},
        {"font",        std::array<Web::Http::EContentType, 2>{Web::Http::EContentType::Woff,
                                                               Web::Http::EContentType::Otf}}
};

dictionary<ECharset, string> charsetMap = {
        {ECharset::UTF_8,        "utf-8"},
        {ECharset::WINDOWS_1251, "windows-1251"}
};

Web::HttpResponse::HttpResponse() = default;

Web::HttpResponse::HttpResponse(object &content) : HttpResponse(JSON::stringify(content)) {
    Web::HttpResponse::contentType = Http::EContentType::Json;
}

Web::HttpResponse::HttpResponse(const string &content) : HttpResponse() {
    Web::HttpResponse::content = content;
}

Web::HttpResponse *Web::HttpResponse::fileResponse(const string &content, const Http::EContentType &contentType) {
    auto response = new HttpResponse();

    response->content = content;
    response->status = Http::EResponseStatus::Ok;
    response->contentType = contentType;

    return response;
}

string Web::HttpResponse::getContentType(const Http::EContentType &contentType) {
    string resultContentType;
    for (auto&[key, value]: HttpResponseTypes) {
        if (contentType >= value[0] && contentType <= value[1]) {
            resultContentType = key;
        }
    }

    return string("${0}/${1}", {resultContentType, StaticFile::getFileContentTypeName(contentType)});
}

string *Web::HttpResponse::pack() {
    if (charset != ECharset::NoneCharset) {
        headers["Content-Type"] = string("${0}; charset=${1}", {getContentType(contentType), getCharsetName(charset)});
    }

    auto responseContent = new string("${0} ${1} \r\n", {version, status});

    for (auto&[key, value] : headers) {
        responseContent->append(string("${0}: ${1}\r\n", {key, value}));
    }

    responseContent->append(string("${0}: ${1}\r\n", {"Content-Length", (Long) content.length()}));

    for (auto &item : cookies) {
        responseContent->append(string("Set-Cookie: ${0}\r\n", {item.toString()}));
    }

    responseContent->append("\r\n").append(content);

    return responseContent;
}

Web::HttpResponse *Web::HttpResponse::setCookie(const Cookie &cookie) {
    cookies.push_back(cookie);

    return this;
}

string Web::HttpResponse::getCharsetName(const ECharset &charsetType) {
    return charsetMap[charsetType];
}

Web::HttpResponse *Web::HttpResponse::ok(object &content) {
    return new HttpResponse(content);
}

Web::HttpResponse *Web::HttpResponse::ok(const string &content) {
    return new HttpResponse(content);
}

Web::HttpResponse *Web::HttpResponse::notFound(object &content) {
    auto response = new HttpResponse(content);

    response->status = Http::EResponseStatus::NotFound;

    return response;
}

Web::HttpResponse *Web::HttpResponse::notFound(const string &content) {
    auto response = new HttpResponse(content);

    response->status = Http::EResponseStatus::NotFound;

    return response;
}

Web::HttpResponse *Web::HttpResponse::badRequest(object &content) {
    auto response = new HttpResponse(content);

    response->status = Http::EResponseStatus::BadRequest;

    return response;
}

Web::HttpResponse *Web::HttpResponse::badRequest(const string &content) {
    auto response = new HttpResponse(content);

    response->status = Http::EResponseStatus::BadRequest;

    return response;
}

Web::HttpResponse *Web::HttpResponse::serverError(object &content) {
    auto response = new HttpResponse(content);

    response->status = Http::EResponseStatus::InternalServerError;

    return response;
}

Web::HttpResponse *Web::HttpResponse::serverError(const string &content) {
    auto response = new HttpResponse(content);

    response->status = Http::EResponseStatus::InternalServerError;

    return response;
}

Web::HttpResponse *Web::HttpResponse::redirect(const string &location) {
    auto response = new HttpResponse();

    response->status = Http::EResponseStatus::MovedPermanently;
    response->headers["Location"] = location;

    return response;
}

Web::HttpResponse *Web::HttpResponse::ok(const object &content) {
    return ok((object &) content);
}
