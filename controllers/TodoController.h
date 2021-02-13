//
// Created by Ivan on 13.02.2021.
//

#ifndef WEBX_TODOCONTROLLER_H
#define WEBX_TODOCONTROLLER_H

#include "../models/others/Store.h"
#include "../lib/ApiController.h"


class TodoController : public Web::ApiController {
public:
    TodoController();

    explicit TodoController(Store *store);

private:
    Store *store = nullptr;

    HttpResponse *addItem(HttpRequest *request);

    HttpResponse *removeItem(HttpRequest *request);
};


#endif //WEBX_TODOCONTROLLER_H
