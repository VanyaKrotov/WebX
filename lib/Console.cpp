//
// Created by Ivan on 19.11.2020.
//

#include "Console.h"
#include <iostream>
#include "JSON.h"
#include "Time.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void Console::writeLine(object &content, const short &color) {
    Json json = JSON::stringify(content);

    writeLine(json, color);
}

void Console::writeLine(const string &content, const short &color) {
    Console::setColor(color);

    std::cout << Time(ETimeZone::CURRENT).toString("[%X]: ") << content << std::endl;

    Console::setColor(EColor::White);
}

void Console::writeLine(const std::initializer_list<string> &content, const short &color) {
    Console::setColor(color);

    std::cout << Time(ETimeZone::CURRENT).toString("[%X]: ");

    for (auto &data: content) {
        std::cout << data << " ";
    }

    std::cout << std::endl;
}

void Console::writeCleanLine(const string &content, const short &color) {
    Console::setColor(color);

    std::cout << content << std::endl;
}

void Console::error(const string &content) {
    writeLine(content, EColor::Red);
}

void Console::setColor(const short &color) {
    SetConsoleTextAttribute(console, color | FOREGROUND_INTENSITY);
}

void Console::warning(const string &content) {
    writeLine(content, EColor::Yellow);
}

void Console::success(const string &content) {
    writeLine(content, EColor::Green);
}

