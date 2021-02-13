#include "lib/WebServer.h"
#include <functional>
#include "controllers/ExampleController.h"


int main(int argsCount, ByteArray *args) {
    auto webServer = new WebServer();

    webServer->use(new ExampleController);

    webServer->useStaticFile();

    webServer->run();
}
