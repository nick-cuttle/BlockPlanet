#include "Server.hpp"
#include <iostream>
#include "../../src/Config.hpp"

int main() {


    try {
        unsigned short port = Config::SERVER_PORT;
        Server server(port);
        server.start();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
