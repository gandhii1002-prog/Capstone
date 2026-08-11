#include <drogon/drogon.h>
#include "util/Database.h"

int main() {
    Database::Instance().Initialize("kishoremart.db");

    drogon::app()
        .loadConfigFile("config.json")
        .run();

    return 0;
}
