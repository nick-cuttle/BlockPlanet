#include "Terrain.hpp"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "Config.hpp"
#include <cmath>


Terrain::Terrain(int s)
    :seed(s)
{ 
}

Terrain::~Terrain()
{
}

void Terrain::render(sf::Vector2f& playerPos, sf::RenderWindow* window)
{

    double chkVisX = ceil(Config::SCREEN_SIZE.width / (Chunk::SIZE * Block::SIZE));
    double chkVisY = ceil(Config::SCREEN_SIZE.height / (Chunk::SIZE * Block::SIZE));
    // Calculate the number of chunks visible on the screen
    int chunksVisibleX = static_cast<int>(chkVisX);
    int chunksVisibleY = static_cast<int>(chkVisY);

    //find all chunks that need to be rendered.
    int playerChunkX = getPlayerChunkX(playerPos.x);
    int playerChunkY = getPlayerChunkY(playerPos.y);

    // Calculate the chunk indices to render
    int halfVisibleX = ceil(static_cast<double>(chunksVisibleX) / 2);
    int halfVisibleY = ceil(static_cast<double>(chunksVisibleY) / 2);

    int rightChunkX = playerChunkX + halfVisibleX;
    int leftChunkX = playerChunkX - halfVisibleX;

    int bottomChunkY = playerChunkY - halfVisibleY;
    int topChunkY = playerChunkY + halfVisibleY; // top most ChunkX

    unrenderChunks(leftChunkX, rightChunkX, topChunkY, bottomChunkY);

    // -LCX: -2 RCX: 2,    TCY: 4   BCY: 2

    //render chunk
    for (int chunkX = leftChunkX; chunkX <= rightChunkX; ++chunkX) {

        for (int chunkY = bottomChunkY; chunkY <= topChunkY; ++chunkY) {
            
            renderChunk(chunkX, chunkY, playerPos, window);
        }
    }

}

//renders a chunk.
//if chunk doesnt exist, create it, else render it.
void Terrain::renderChunk(int chunkX, int chunkY, sf::Vector2f& playerPos, sf::RenderWindow* window)
{
    // Look to see if chunk already exists.
    bool foundChunk = false;
    for (const Chunk& curChunk : chunks) { 

        if (curChunk.getChunkX() == chunkX && curChunk.getChunkY() == chunkY) {

            foundChunk = true;
            break;
        }
    }


    if (!foundChunk) {
        Chunk newChunk {chunkX, chunkY};
        newChunk.generate(this->seed);
        chunks.push_back(std::move(newChunk));
    }

    Chunk* chunk = getChunk(chunkX, chunkY);
    if (!chunk) {
        std::cout << "CHUNK NOT FOUND WTTTTFFFFFFF" << std::endl;
        return;
    }
    // if (chunk->getChunkX() == 1 && chunk->getChunkY() == 0) {
    //     //chunk->print();
    //     chunk->updateBlockPositions(playerPos);
    //     chunk->draw(window);
    // }
    // if (chunk->getChunkX() == 0 && chunk->getChunkY() == 1) {
    //     //chunk->print();
    //     chunk->updateBlockPositions(playerPos);
    //     chunk->draw(window);
    // }
    chunk->updateBlockPositions(playerPos);
    chunk->draw(window);
    
}

//unrender all chunks that are no longer visible.
void Terrain::unrenderChunks(int lChunkX, int rChunkX, int tChunkY, int bChunkY)
{
    // Create an iterator to loop through the chunks
    std::vector<Chunk>::iterator chunkIter = chunks.begin();

    while (chunkIter != chunks.end()) {

        // Check if the current chunk is outside the visible range, erase if so.
        if (chunkIter->getChunkX() > rChunkX || chunkIter->getChunkX() < lChunkX ||
            chunkIter->getChunkY() < bChunkY || chunkIter->getChunkY() > tChunkY) {
            chunkIter = chunks.erase(chunkIter); 
        } else {
            ++chunkIter;
        }
    }
}

Chunk* Terrain::getChunk(int chunkX, int chunkY)
{
    for (Chunk& curChunk : chunks) { 

        if (curChunk.getChunkX() == chunkX && curChunk.getChunkY() == chunkY) {
            return &curChunk;
        }
    }
    return NULL;
}
