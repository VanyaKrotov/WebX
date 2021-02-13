//
// Created by Ivan on 19.11.2020.
//

#include "HttpRequest.h"
#include <cstdio>
#include <chrono>
#include "vector.h"
#include "Console.h"

/*
 * Старый код
    auto start_0 = std::chrono::steady_clock::now();

    auto end_0 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_0 = end_0 - start_0;
    Console::writeLine(elapsed_seconds_0.count());

    auto start = std::chrono::steady_clock::now();

    const size_t length = request->length();
    int indexFirstRow = request->find("\r\n");
    int indexStartBody = request->find("\r\n\r\n", indexFirstRow + 2);

    string firstRow = request->substr(0, indexFirstRow);
    string head = request->substr(indexFirstRow + 2, indexStartBody - indexFirstRow - 2);
    body = request->substr(indexStartBody + 4, length - indexStartBody + 4);

    vector<string> firstRowData = firstRow.split(" ");

    httpType = HttpRequest::getTypeByName(firstRowData[2]);

    href = HttpRequest::urlDecode(firstRowData[1]);
    vector<string> parsedData = href.split("?");
    const int parseDataLength = parsedData.length();

    path = parseDataLength ? parsedData[0] : "";
    if (parseDataLength > 1) {
        query = Query::parse(parsedData[1]);
    }

    vector<string> headersContent = head.split("\r\n");
    for (string header : headersContent) {
        vector<string> header_ = header.split(": ");
        if (header_.length() == 2) {
            headers[header_[0]] = header_[1];
        }
    }

    if (headers.hasKey("Cookie")) {
        HttpRequest::cookies = Cookie::parse(headers["Cookie"]);
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    Console::writeLine(elapsed_seconds.count());

     if (headers["Content-Type"] == "application/x-www-form-urlencoded") {
         string decodeBody = HttpRequest::urlDecode(body);
         body = URLToJson(decodeBody);
     }

*/

dictionary <string, Web::EHttpType> HttpTypesConnectionTable = {
        {"GET",     Web::EHttpType::GET},
        {"POST",    Web::EHttpType::POST},
        {"PUT",     Web::EHttpType::PUT},
        {"DELETE",  Web::EHttpType::DEL},
        {"OPTIONS", Web::EHttpType::OPTIONS}
};

string Web::HttpRequest::urlDecode(string &data) {
    string result;
    int dIndex;
    size_t length = data.length();

    for (int index = 0; index < length; index++) {
        if (data[index] != '%') {
            if (data[index] == '+') {
                result += ' ';
            } else {
                result += data[index];
            }
        } else {
            sscanf_s(data.substr(index + 1, 2).c_str(), "%x", &dIndex);
            result += static_cast<char>(dIndex);
            index += 2;
        }
    }

    return result;
}

string Web::HttpRequest::urlEncode(string &data) {
    string result;
    Byte c;
    int ic;
    const char *chars = data.c_str();
    char bufHex[10];
    int length = (int) strlen(chars);

    for (int index = 0; index < length; index++) {
        c = chars[index];
        ic = c;

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            result += c;
        } else {
            sprintf_s(bufHex, "%X", c);
            if (ic < 16)
                result += "%0";
            else
                result += "%";
            result += bufHex;
        }
    }

    return result;
}

Web::HttpRequest::HttpRequest(string *request) {
    if (request->empty()) {
        return;
    }

    requestHeadersParser(*request);

    delete request;
}

Web::EHttpType Web::HttpRequest::getTypeByName(const string &data) {
    return HttpTypesConnectionTable[data];
}

void Web::HttpRequest::requestHeadersParser(const string &request) {
    const size_t length = request.length();
    size_t index = 0;

    string method;
    while (request[index] != ' ') {
        method.push_back(request[index]);
        index++;
    }

    httpType = HttpRequest::getTypeByName(method);

    index++;

    while (request[index] != ' ') {
        href.push_back(request[index]);
        index++;
    }

    href = HttpRequest::urlDecode(href);

    {
        const size_t hrefLength = href.length();
        int i = 0;
        for (; href[i] != '?' && i < hrefLength; i++) {
            path.push_back(href[i]);
        }

        if (i < hrefLength) {
            i++;

            string queryString;
            for (; i < hrefLength; i++) {
                queryString.push_back(href[i]);
            }

            query = Query::parse(queryString);
        }
    }

    index++;

    while (request[index] != '\n') {
        index++;
    }

    index++;

    index = headersParse(request, index);

    index += 2;

    if (request[index] != '\0') {
        while (index < length) {
            body.push_back(request[index]);
            index++;
        }
    }
}

size_t Web::HttpRequest::headersParse(const string &request, const size_t &index) {
    int i = index;
    string key;
    string value;
    while (request[i] != ':') {
        key.push_back(request[i]);
        i++;
    }

    i += 2;

    while (request[i] != '\r') {
        value.push_back(request[i]);
        i++;
    }

    i += 2;

    headers[key] = value;

    if (request[i] == '\r') {
        return i;
    }

    return headersParse(request, i);
}