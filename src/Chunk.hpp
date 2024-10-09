#pragma once
#include "blocks/Block.hpp"
#include <vector>

class Chunk {

public:
    static const int SIZE = 16;


private:

    int chunkX;
    int chunkY;
    std::vector<std::vector<Block*>> blocks;


public:

    Chunk();

    Chunk(int cX, int cY);

    ~Chunk();

    int getChunkX() const { return chunkX; }

    int getChunkY() const { return chunkY; }

    void generate(int seed);

    void draw(sf::RenderWindow* window);
    
    void updateBlockPositions(sf::Vector2f& playerPos);

    Chunk(const Chunk &) = delete; // Prevent copying

    void print();

    Chunk(Chunk &&other)
    {
        this->chunkX = other.chunkX;
        this->chunkY = other.chunkY;
        this->blocks = std::move(other.blocks);

        other.blocks = std::vector<std::vector<Block*>>(Chunk::SIZE, std::vector<Block*>(Chunk::SIZE, nullptr));

    }

    // Move assignment operator
    Chunk& operator=(Chunk&& other) noexcept {
        if (this != &other) {
            chunkX = other.chunkX;
            chunkY = other.chunkY;
            blocks = std::move(other.blocks);
            other.blocks = std::vector<std::vector<Block*>>(Chunk::SIZE, std::vector<Block*>(Chunk::SIZE, nullptr));

        }
        return *this;
    }

    // // Copy constructor
    // Chunk(const Chunk& other) {
    //     chunkX = other.chunkX;
    //     chunkY = other.chunkY;
    //     blocks = other.blocks; 

    // }

    // Copy assignment operator
    Chunk& operator=(const Chunk& other) {
        if (this != &other) {
            chunkX = other.chunkX;
            chunkY = other.chunkY;
            blocks = other.blocks;

        }
        return *this;
    }


};