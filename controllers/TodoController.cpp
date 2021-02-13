//
// Created by Ivan on 13.02.2021.
//

#include "TodoController.h"
#include "../lib/ObjectField.h"

TodoController::TodoController(Store *store) : TodoController() {
    TodoController::store = store;
}

TodoController::TodoController() {
    routePrefix = "/api/todo/";

    bindAction(Route::post("add", [this](HttpRequest *request) {
        return addItem(request);
    }));

    bindAction(Route::del("remove/{number:itemId}", [this](HttpRequest *request) {
        return removeItem(request);
    }));

    bindAction(Route::get("all", [this](HttpRequest *request) {
        return this->ok(store->items);
    }));
}

HttpResponse *TodoController::addItem(HttpRequest *request) {
    auto itemData = request->getDataFromBody<TodoItem>();

    return ok(store->addItem(itemData));
}

HttpResponse *TodoController::removeItem(HttpRequest *request) {
    const int itemId = request->query["itemId"].toInt();

    store->removeItem(itemId);

    return ok("");
}

