#include "lib/WebServer.h"
#include <functional>
#include "controllers/TodoController.h"
#include "models/others/Store.h"

int main(int argsCount, ByteArray *args) {
    auto webServer = new WebServer();

    auto store = new Store();

    webServer->use(new TodoController(store));

    webServer->useStaticFile();

    webServer->run();
}
