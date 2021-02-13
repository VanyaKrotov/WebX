//
// Created by Ivan on 19.11.2020.
//

#ifndef WEBX_STRINGIFYENGINE_H
#define WEBX_STRINGIFYENGINE_H

#include "JSONOptions.h"

namespace JSON {
    class StringifyEngine {
    private:
        string resultJson;
        string firstSpace;
        string itemSpace;

        void deleteLastComa();
    public:
        explicit StringifyEngine(JSON::JSONOptions& options);
        void addItem(const string& item);
        void addItem(const string& key, const string& value);
        string getJsonObject();
        string getJsonArray();
    };
}


#endif //WEBX_STRINGIFYENGINE_H
