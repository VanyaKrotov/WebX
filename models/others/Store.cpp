//
// Created by Ivan on 13.02.2021.
//

#include "Store.h"

TodoItem &Store::addItem(TodoItem *item) {
    item->id = items.length() + 1;

    items.push_back(*item);

    return *item;
}

void Store::removeItem(const int &id) {
    const int findIndex = items.findIndexOf([id](TodoItem &item, const int &index) {
        return item.id && *item.id == id;
    });

    if (findIndex != -1) {
        items.remove(findIndex);
    }
}
