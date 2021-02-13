//
// Created by Ivan on 13.02.2021.
//

#ifndef WEBX_ISTORE_H
#define WEBX_ISTORE_H

#include "../../lib/vector.h"
#include "../serialize/TodoItem.h"

struct IStore {
    vector<TodoItem> items;
};

#endif //WEBX_ISTORE_H
