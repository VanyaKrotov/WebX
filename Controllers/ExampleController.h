//
// Created by Ivan on 13.02.2021.
//

#ifndef TESTCLION_EXAMPLECONTROLLER_H
#define TESTCLION_EXAMPLECONTROLLER_H

#include "../Lib/Controller.h"

struct IFormData {
    string firstName;
    string lastName;
    string age;
};

struct FormData : public object, public IFormData {
    FormData();
};

struct IPostResponse {
    Long id = 0;
    vector<dictionary<string, string>> array = {{}, {}, {}};
    FormData *copyData = nullptr;
};

struct PostResponse : public FormData, public IPostResponse {
    static Long idNum;

    PostResponse();
};

class ExampleController : public Controller {
public:
    ExampleController();

private:
    HttpResponse *postRequest(HttpRequest *request, FormData &formData);

    HttpResponse *getRequest(HttpRequest *request, const int &paramId);
};


#endif //TESTCLION_EXAMPLECONTROLLER_H
