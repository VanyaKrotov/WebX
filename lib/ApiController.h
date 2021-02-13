//
// Created by Ivan on 13.02.2021.
//

#ifndef WEBX_APICONTROLLER_H
#define WEBX_APICONTROLLER_H

#include "Controller.h"

namespace Web {
    class ApiController : public Controller {
    protected:
        Http::EContentType contentType = Http::EContentType::Json;
    };
}

#endif //WEBX_APICONTROLLER_H