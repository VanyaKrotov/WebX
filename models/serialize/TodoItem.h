//
// Created by Ivan on 13.02.2021.
//

#ifndef WEBX_TODOITEM_H
#define WEBX_TODOITEM_H


#include "../interfaces/ITodoItem.h"
#include "../../lib/object.h"
#include "../../lib/ObjectField.h"

class TodoItem : public ITodoItem, public object {
public:
    //    static int itemCount;

    TodoItem() {
        bindField(new JSON::ObjectField("id", id));
        bindField(new JSON::ObjectField("title", title));
        bindField(new JSON::ObjectField("description", description));
        bindField(new JSON::ObjectField("state", state));
    }
};

#endif //WEBX_TODOITEM_H
