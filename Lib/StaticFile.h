//
// Created by Ivan on 12.02.2021.
//

#ifndef WEBX_STATICFILE_H
#define WEBX_STATICFILE_H

#include "HttpResponse.h"
#include "EContentType.h"

namespace Web {
    struct FileContent {
        string content;
        Http::EContentType contentType;
    };

    class StaticFile {
    public:
        static dictionary<Http::EContentType, string> fileTypesMapReverse;
        static dictionary<string, Http::EContentType> fileTypesMap;

        static HttpResponse *getStaticFile(const string &filePath);

        static FileContent getFileContent(const string &filePath);

        static Http::EContentType getFileContentType(const string &fileName);

        static string &getFileContentTypeName(const Http::EContentType &type);
    };

}


#endif //WEBX_STATICFILE_H
