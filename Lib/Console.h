//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_CONSOLE_H
#define WEBX_CONSOLE_H

#include "object.h"
#include <windows.h>

enum EColor {
    Blue = 1,
    Green = 2,
    Aqua = 3,
    Red = 4,
    Purple = 5,
    Yellow = 6,
    White = 7,
    Gray = 8
};

class Console {
private:
    static void setColor(const short &color = EColor::White);

public:

    static void writeLine(const string &content, const short &color = EColor::White);

    static void writeCleanLine(const string &content, const short &color = EColor::White);

    static void error(const string &content);

    static void warning(const string &content);

    static void success(const string &content);

    static void writeLine(const std::initializer_list<string> &content, const short &color = EColor::White);

    static void writeLine(object &content, const short &color = EColor::White);
};

#endif //WEBX_CONSOLE_H
