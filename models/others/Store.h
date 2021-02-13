//
// Created by Ivan on 13.02.2021.
//

#ifndef WEBX_STORE_H
#define WEBX_STORE_H

#include "../interfaces/IStore.h"

class Store : public IStore {
public:
    TodoItem &addItem(TodoItem *item);

    void removeItem(const int &id);
};


#endif //WEBX_STORE_H
