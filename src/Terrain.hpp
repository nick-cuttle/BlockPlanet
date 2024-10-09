#pragma once
#include "blocks/Block.hpp"
#include "blocks/GrassBlock.hpp"
#include <vector>
#include "Chunk.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

class Terrain {
private:

    std::vector<Chunk> chunks;
    int seed;


public:

    Terrain(int seed);
    ~Terrain();
    
    void render(sf::Vector2f& playerPos, sf::RenderWindow* window);


private:

    void renderChunk(int chunkX, int chunkY, sf::Vector2f& playerPos, sf::RenderWindow* window);

    void unrenderChunks(int lChunkX, int rChunkX, int tChunkY, int bChunkY);

    Chunk* getChunk(int chunkX, int chunkY);

    // inline int getPlayerChunk(float coord) {
    //     return static_cast<int>(std::floor(coord / (Chunk::SIZE * Block::SIZE)));
    // }

    inline int getPlayerChunkX(float coord) {
        int chunkIndex;
        if (coord >= 0) {
            chunkIndex = static_cast<int>(std::floor(coord / (Chunk::SIZE * Block::SIZE)));
        }
        else{
            chunkIndex = -1 + static_cast<int>(std::ceil(coord / (Chunk::SIZE * Block::SIZE)));
        }
        return chunkIndex;
    }

    inline int getPlayerChunkY(float coord) {
        int chunkIndex;
        if (coord <= 0) {
            chunkIndex = static_cast<int>(std::ceil(coord / (Chunk::SIZE * Block::SIZE)));
        }
        else{
            chunkIndex = 1 + static_cast<int>(std::floor(coord / (Chunk::SIZE * Block::SIZE)));
        }
        return chunkIndex;
    }

};