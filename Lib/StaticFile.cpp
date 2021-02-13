//
// Created by Ivan on 12.02.2021.
//

#include <fstream>
#include <filesystem>
#include "StaticFile.h"

using namespace Web;

dictionary<Http::EContentType, string> StaticFile::fileTypesMapReverse = {
        {Http::EContentType::Html, "html"},
        {Http::EContentType::Txt,  "txt"},
        {Http::EContentType::Js,   "js"},
        {Http::EContentType::Json, "json"},
        {Http::EContentType::Css,  "css"},
        {Http::EContentType::Doc,  "doc"},
        {Http::EContentType::Docx, "docx"},
        {Http::EContentType::Rtf,  "rtf"},
        {Http::EContentType::Pdf,  "pdf"},
        {Http::EContentType::Mp3,  "mp3"},
        {Http::EContentType::Wav,  "wav"},
        {Http::EContentType::Mp4,  "mp4"},
        {Http::EContentType::Webm, "webm"},
        {Http::EContentType::Avi,  "avi"},
        {Http::EContentType::Flv,  "flv"},
        {Http::EContentType::Zip,  "zip"},
        {Http::EContentType::Rar,  "rar"},
        {Http::EContentType::SZip, "7zip"},
        {Http::EContentType::Png,  "png"},
        {Http::EContentType::Img,  "img"},
        {Http::EContentType::Ico,  "ico"},
        {Http::EContentType::Jpg,  "jpg"},
        {Http::EContentType::Jpeg, "jpeg"},
        {Http::EContentType::Gif,  "gif"},
        {Http::EContentType::Bmp,  "bmp"},
        {Http::EContentType::Tiff, "tiff"},
        {Http::EContentType::Woff, "woff"},
        {Http::EContentType::Ttf,  "ttf"},
        {Http::EContentType::Otf,  "otf"},
};

dictionary<string, Http::EContentType> StaticFile::fileTypesMap = {
        {"html", Http::EContentType::Html},
        {"txt",  Http::EContentType::Txt},
        {"js",   Http::EContentType::Js},
        {"json", Http::EContentType::Json},
        {"css",  Http::EContentType::Css},
        {"doc",  Http::EContentType::Doc},
        {"docx", Http::EContentType::Docx},
        {"rtf",  Http::EContentType::Rtf},
        {"pdf",  Http::EContentType::Pdf},
        {"mp3",  Http::EContentType::Mp3},
        {"wav",  Http::EContentType::Wav},
        {"mp4",  Http::EContentType::Mp4},
        {"webm", Http::EContentType::Webm},
        {"avi",  Http::EContentType::Avi},
        {"flv",  Http::EContentType::Flv},
        {"zip",  Http::EContentType::Zip},
        {"rar",  Http::EContentType::Rar},
        {"7zip", Http::EContentType::SZip},
        {"png",  Http::EContentType::Png},
        {"img",  Http::EContentType::Img},
        {"ico",  Http::EContentType::Ico},
        {"jpg",  Http::EContentType::Jpg},
        {"jpeg", Http::EContentType::Jpeg},
        {"gif",  Http::EContentType::Gif},
        {"bmp",  Http::EContentType::Bmp},
        {"tiff", Http::EContentType::Tiff},
        {"woff", Http::EContentType::Woff},
        {"ttf",  Http::EContentType::Ttf},
        {"otf",  Http::EContentType::Otf},
};

HttpResponse *StaticFile::getStaticFile(const string &filePath) {
    try {
        auto[content, contentType] = StaticFile::getFileContent(filePath);

        const auto response = new HttpResponse(content);

        response->contentType = contentType;

        response->charset = ECharset::UTF_8;

        return response;
    } catch (const std::exception &exception) {
        return nullptr;
    }
}

FileContent StaticFile::getFileContent(const string &filePath) {
    auto file = std::ifstream(filePath, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        throw std::exception();
    }

    const auto contentType = StaticFile::getFileContentType(filePath);
    auto length = std::filesystem::file_size(filePath.c_str());

    file.seekg(0, std::ios::beg);

    auto buffer = new Byte[length];

    file.read(buffer, length);

    string fileContent;

    fileContent.assign(buffer, length);
    delete[] buffer;

    return {fileContent, contentType};
}

Http::EContentType StaticFile::getFileContentType(const string &fileName) {
    const auto dotPosition = fileName.find_last_of('.');
    const auto typeName = fileName.substr(dotPosition + 1, fileName.length() - dotPosition - 1);

    if (StaticFile::fileTypesMap.hasKey(typeName)) {
        return StaticFile::fileTypesMap[typeName];
    }

    return Http::EContentType::NoneType;
}

string &StaticFile::getFileContentTypeName(const Http::EContentType &type) {
    return StaticFile::fileTypesMapReverse[type];
}
