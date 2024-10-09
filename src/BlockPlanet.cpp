
#include "Client.hpp"
#include "blocks/Block.hpp"
#include <iostream>
#include "Terrain.hpp"

int main()
{   

    // //Chunk c10 {1, 0};
    // Chunk c00 {0, 0};
    // // // Chunk c01 {0, -1};
    // c00.generate(12345);
    // //c10.generate(12345);
    // //c10.print();
    // c00.print();

    // while (true) {}
    // return EXIT_SUCCESS;
    Client client{};

    client.connect();

    client.run();

    return EXIT_SUCCESS;
}
