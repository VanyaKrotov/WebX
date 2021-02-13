//
// Created by Ivan on 11.02.2021.
//

#include "Controller.h"

Controller *Controller::bindAction(Route *route) {
    routes.push_back(route);

    return this;
}

Controller::Controller() = default;

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

HttpResponse *Controller::ok(const string &content) {
    return new HttpResponse(content, contentType);
}

HttpResponse *Controller::ok(object &content) {
    return new HttpResponse(content, contentType);
}

HttpResponse *Controller::notFound(const string &content) {
    return new HttpResponse(content, contentType, Http::EResponseStatus::NotFound);
}

HttpResponse *Controller::notFound(object &content) {
    return new HttpResponse(content, contentType, Http::EResponseStatus::NotFound);
}

HttpResponse *Controller::badRequest(const string &content) {
    return new HttpResponse(content, contentType, Http::EResponseStatus::BadRequest);
}

HttpResponse *Controller::badRequest(object &content) {
    return new HttpResponse(content, contentType, Http::EResponseStatus::BadRequest);
}

