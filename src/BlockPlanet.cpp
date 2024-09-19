
#include "Client.hpp"
#include "blocks/Block.hpp"

int main()
{   
    Client client{};

    client.connect();

    client.run();

    return EXIT_SUCCESS;
}
