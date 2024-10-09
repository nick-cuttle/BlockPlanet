#include "Chunk.hpp"
#include <iostream>
#include <FastNoiseLite.h>
#include <cmath>
#include "blocks/GrassBlock.hpp"

Chunk::Chunk(int cX, int cY)
    :
    chunkX(cX),
    chunkY(cY),
    blocks(Chunk::SIZE, std::vector<Block*>(Chunk::SIZE, nullptr))
{
}

Chunk::~Chunk()
{
    for (int x = 0; x < Chunk::SIZE; ++x) {

        for (int y = 0; y < Chunk::SIZE; ++y) {
            delete blocks[x][y];
        }
    }
}

void Chunk::generate(int seed)
{
    //chunks above the top dont get blocks (nullptr == air)
    // if (chunkY > 0) {
    //     return;
    // }
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetSeed(seed);
    
    //surface height map for this range of x's.
    std::vector<int> surfaceHeightMap(Chunk::SIZE);
    int x_begin = chunkX * Chunk::SIZE;
    int x_end = x_begin + (Chunk::SIZE - 1);
    int y_begin = chunkY * Chunk::SIZE;
    int y_end = y_begin - (Chunk::SIZE - 1);

    //Normal Terrain:
    //S: 1.5
    //H: 100

    float noiseScale = .35;  // Adjust for terrain smoothness
    int MAX_TERRAIN_HEIGHT = 100; //Max Height

    // Generate height map for the chunk
    // Each chunk generates a height map. 
    // If it is a top chunk (chunkY == 0), it uses Perlin noise to calculate its height map.
    // For non-top chunks, the height map is derived from the top chunk's height map using an offset.
    // This allows for consistent terrain generation, where blocks below the top layer are filled in 
    // by decrementing the height based on their relative position to the top layer.
    for (int localX = x_begin; localX <= x_end; ++localX) {
        // Scale noise value to the height range [0, MAX_HEIGHT]
        float scaledHeight = (noise.GetNoise(localX * noiseScale, 0.0f) + 1) * (MAX_TERRAIN_HEIGHT / 2.0f);

        int height = static_cast<int>(round(scaledHeight));

        surfaceHeightMap[localX - x_begin] = height;

    }

    // for (int h : surfaceHeightMap) {
    //     std::cout << h << " ";
    // }
    // std::cout << std::endl;

    //create blocks.
    for (int blockX = x_begin; blockX <= x_end; ++blockX) {

        int surfaceHeightX = surfaceHeightMap[blockX - x_begin]; //get surface height for x.
        bool isSurfaceForX = false;

        //check if this chunks x contains the surface.
        if (surfaceHeightX <= y_begin && surfaceHeightX >= y_end) {
            isSurfaceForX = true;
        }

        for (int blockY = y_begin; blockY >= y_end; --blockY) {
            
            //check if surface height is in this chunk
            if (isSurfaceForX) {
                
                //blocks higher than surface height air
                if (blockY > surfaceHeightX) {
                    blocks[blockX - x_begin][y_begin - blockY] = nullptr;
                }
                else {
                    blocks[blockX - x_begin][y_begin - blockY] = new GrassBlock({blockX, blockY});
                }
            }
            //chunks not surface chunks and above surface height place air
            else if (!isSurfaceForX && y_end > surfaceHeightX) {
                blocks[blockX - x_begin][y_begin - blockY] = nullptr;
            }
            //not surface nor above it, solid blocks.
            else {
                blocks[blockX - x_begin][y_begin - blockY] = new GrassBlock({blockX, blockY});
            }

            
        } //end y for loop
    } //end x for loop

}

void Chunk::print() {

    std::cout << "Chunk: (" << chunkX << ", " << chunkY << ")" << std::endl;

    for (int blockX = 0; blockX < Chunk::SIZE; ++blockX) {

        for (int blockY = 0; blockY < Chunk::SIZE; ++blockY) {
            
            Block* b = blocks[blockX][blockY];
            if (!b) { continue; }
            std::cout << "X: " << b->getPosition().x << ", Y: " << b->getPosition().y << std::endl;
        }
    }
    std::cout << "====================== End Of Chunk =======================" << std::endl;
}

void Chunk::draw(sf::RenderWindow* window)
{
    for (std::vector<Block*>& row : blocks) {

        for (Block* block : row) {
            if (block) {
                block->draw(window);
            }
        }
    }
}

void Chunk::updateBlockPositions(sf::Vector2f &playerPos)
{
    for (std::vector<Block*>& row : blocks) {

        for (Block* block : row) {

            if (block) {
                block->updatePosition(playerPos);
            }
        }
    }
}
