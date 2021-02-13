//
// Created by Ivan on 11.02.2021.
//

#ifndef WEBX_CONTROLLER_H
#define WEBX_CONTROLLER_H

#include <functional>
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "Route.h"
#include "vector.h"

using namespace Web;


namespace Web {
    class Controller {
    private:
        vector<Route *> routes;


    public:
        Controller();

        ControllerAction *findAction(HttpRequest *request);

    protected:
        Http::EContentType contentType = Http::EContentType::Html;
        string routePrefix;

        Controller *bindAction(Route *route);

        virtual HttpResponse *ok(const string &content);

        virtual HttpResponse *ok(object &content);

        virtual HttpResponse *badRequest(const string &content);

        virtual HttpResponse *badRequest(object &content);

        virtual HttpResponse *notFound(const string &content);

        virtual HttpResponse *notFound(object &content);
    };
}


#endif //WEBX_CONTROLLER_H
