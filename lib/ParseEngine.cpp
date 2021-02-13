//
// Created by Ivan on 19.11.2020.
//

#include "ParseEngine.h"

#include <utility>
#include "string.h"

void JSON::ParseEngine::parseObject(Json json, const std::function<void(string, string)> &returnFn) {
    if (json.isEmpty()) {
        return;
    }

    const size_t openBracket = json.find_first_of(OPEN_BRACKET_OBJECT);
    const size_t closeBracket = json.find_last_of(CLOSE_BRACKET_OBJECT);

    Json jsonOpenObject = json.substr(openBracket + 1, closeBracket - openBracket - 1);

    const size_t jsonLength = jsonOpenObject.length();
    int position = 0;

    while (position < jsonLength) {
        const int startKeyPosition = jsonOpenObject.find_first_of('"', position);
        const int endKeyPosition = jsonOpenObject.find_first_of('"', startKeyPosition + 1);
        const int startValuePosition = jsonOpenObject.find_first_of(':', endKeyPosition + 1);

        int openBracketsCount = 0;
        int quotes = 0;
        int caretPosition = startValuePosition + 1;

        while (!((jsonOpenObject[caretPosition] == ',' || jsonOpenObject[caretPosition] == '\0') &&
                 !openBracketsCount && !(quotes % 2))) {
            const bool isQuote = jsonOpenObject[caretPosition] == '"';
            if (!isQuote) {
                const bool isOpenBracket =
                        jsonOpenObject[caretPosition] == OPEN_BRACKET_OBJECT ||
                        jsonOpenObject[caretPosition] == OPEN_BRACKET_ARRAY;
                const bool isCloseBracket =
                        jsonOpenObject[caretPosition] == CLOSE_BRACKET_OBJECT ||
                        jsonOpenObject[caretPosition] == CLOSE_BRACKET_ARRAY;

                openBracketsCount += isOpenBracket ? 1 : isCloseBracket ? -1 : 0;
            }

            quotes += (int) (isQuote);
            caretPosition++;
        }

        string key = jsonOpenObject.substr(startKeyPosition + 1, endKeyPosition - startKeyPosition - 1);
        Json value = jsonOpenObject.substr(startValuePosition + 1, caretPosition - startValuePosition - 1);

        returnFn(key, value);

        position = caretPosition + 1;
    }
}

void JSON::ParseEngine::parseArray(Json json, const std::function<void(Json)> &returnFn) {
    if (json.isEmpty()) {
        return;
    }

    const size_t openBracket = json.find_first_of(OPEN_BRACKET_ARRAY);
    const size_t closeBracket = json.find_last_of(CLOSE_BRACKET_ARRAY);

    Json jsonOpenArray = json.substr(openBracket + 1, closeBracket - openBracket - 1);

    const size_t jsonLength = jsonOpenArray.length();

    int caretPosition = 0;
    while (caretPosition < jsonLength) {
        Json value;
        int openBracketsCount = 0;
        bool isWorkParseWhile = true;

        while (isWorkParseWhile) {
            const bool isOpenBracket =
                    jsonOpenArray[caretPosition] == OPEN_BRACKET_OBJECT ||
                    jsonOpenArray[caretPosition] == OPEN_BRACKET_ARRAY;
            const bool isCloseBracket =
                    jsonOpenArray[caretPosition] == CLOSE_BRACKET_OBJECT ||
                    jsonOpenArray[caretPosition] == CLOSE_BRACKET_ARRAY;

            openBracketsCount += isOpenBracket ? 1 : isCloseBracket ? -1 : 0;
            value.push_back(jsonOpenArray[caretPosition]);

            caretPosition++;

            const bool isCommaOrEnd = jsonOpenArray[caretPosition] == ',' || jsonOpenArray[caretPosition] == '\0';

            isWorkParseWhile = !(isCommaOrEnd && !openBracketsCount);
        }

        returnFn(value);

        caretPosition++;
    }
}
