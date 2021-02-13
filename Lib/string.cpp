//
// Created by Ivan on 18.11.2020.
//

#include "string.h"
#include <regex>
#include <utility>
#include "vector.h"

string::string() : std::string() {}

string::string(CByteArray value) : std::string(value) {}

string::string(ByteArray value) : std::string(value) {}

string::string(int value) : std::string(std::to_string(value)) {}

string::string(double value) : std::string(std::to_string(value)) {}

string::string(float value) : std::string(std::to_string(value)) {}

string::string(Long value) : std::string(std::to_string(value)) {}

string::string(bool value) : std::string(value ? "true" : "false") {}

string::string(DLong value) : std::string(std::to_string(value)) {}

string::string(std::string value) : std::string(std::move(value)) {}

string::string(Byte value) : std::string(std::to_string(value)) {}

string::string(string templateString, std::initializer_list<string> items) {
    *this = std::move(templateString);

    int index = 0;
    for (const string &injectionString: items) {
        string findTemplate = string("${" + string(index) + "}");

        const size_t findTemplateLength = findTemplate.length();
        int lastPosition = this->find(findTemplate);
        while (lastPosition != -1) {
            this->replace(lastPosition, findTemplateLength, injectionString);

            lastPosition = this->find(findTemplate, lastPosition);
        }

        index++;
    }
}

bool string::isEmpty() {
    return this->empty();
}

double string::toDouble() {
    return std::stod(*this);
}

bool string::toBool() {
    return this->find("true") != -1;
}

Long string::toLong() {
    return std::stol(*this);
}

int string::toInt() {
    return std::stoi(*this);
}

bool string::regexSearch(const string &regexString) {
    return std::regex_search(*this, std::regex(regexString));
}

string string::trim() {
    string result = *this;

    result.erase(0, result.find_first_not_of(' '));
    result.erase(result.find_last_not_of(' ') + 1);

    return result;
}

string string::operator*(int count) {
    string result;

    for (int index = 0; index < count; index++) {
        result.append(*this);
    }

    return result;
}

vector<string> string::split(const string &separator) {
    vector<string> result;

    const int separatorLength = separator.length();
    int Start = 0;
    int Pointer = find_first_of(separator);

    while (Pointer != npos) {
        result.push_back(substr(Start, Pointer - Start));
        Start = separatorLength + Pointer;
        Pointer = find_first_of(separator, separatorLength + Pointer);

        if (Pointer == npos)
            result.push_back(substr(Start, length()));
    }

    if (result.length() == 0 && length() != 0) {
        result.push_back(*this);
    }

    return result;
}








