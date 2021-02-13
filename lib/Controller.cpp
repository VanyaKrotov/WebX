//
// Created by Ivan on 11.02.2021.
//

#include "Controller.h"

Controller *Controller::bindAction(Route *route) {
    routes.push_back(route);

    return this;
}

Controller::Controller() {}

ControllerAction *Controller::findAction(HttpRequest *request) {
    const short prefixLength = routePrefix.length();
    if (routes.empty() || (prefixLength > 0 && request->path.substr(0, prefixLength) != routePrefix)) {
        return nullptr;
    }

    for (auto route: routes) {
        auto findAction = route->findAction(request, prefixLength);

        if (findAction) {
            return findAction;
        }
    }

    return nullptr;
}
