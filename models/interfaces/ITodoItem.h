//
// Created by Ivan on 13.02.2021.
//

#ifndef WEBX_ITODOITEM_H
#define WEBX_ITODOITEM_H

#include "../../lib/string.h"

enum EItemState {
    Done = '0',
    InProgress = '1',
    ToDo = '2'
};

struct ITodoItem {
    int id = 0;
    string title;
    string description;
    string state = EItemState::ToDo;
};

#endif //WEBX_ITODOITEM_H
