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
        string routePrefix;

        Controller *bindAction(Route *route);
    };
}


#endif //WEBX_CONTROLLER_H
