//
// Created by Ivan on 13.02.2021.
//

#include "ExampleController.h"
#include "../Lib/ObjectField.h"

Long PostResponse::idNum = 0;

FormData::FormData() {
    bindField(new JSON::ObjectField("firstName", firstName));
    bindField(new JSON::ObjectField("lastName", lastName));
    bindField(new JSON::ObjectField("age", age));
}

PostResponse::PostResponse() {
    bindField(new JSON::ObjectField("id", id));
    bindField(new JSON::ObjectField("array", array));
    bindField(new JSON::ObjectField("copyData", copyData));
}


HttpResponse *ExampleController::postRequest(HttpRequest *request, FormData &formData) {
    auto result = formData.mapTo<PostResponse>();

    result->id = ++PostResponse::idNum;

    return HttpResponse::ok(*result);
}

HttpResponse *ExampleController::getRequest(HttpRequest *request, const int &paramId) {
    const bool res = true;
    auto content = dictionary<string, string>{{"paramId", paramId},
                                              {"get",     res}};

    return HttpResponse::ok(content);
}

ExampleController::ExampleController() {
    routePrefix = "/api/example/";

    bindAction(Route::post("post", [this](HttpRequest *request) {
        auto formData = request->getDataFromBody<FormData>();

        return postRequest(request, formData);
    }));

    bindAction(Route::get("get/{number:paramId}", [this](HttpRequest *request) {
        auto paramId = request->query["paramId"].toInt();

        return getRequest(request, paramId);
    }));
}
