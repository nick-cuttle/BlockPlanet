#include "TexureManager.hpp"
#include <iostream>


sf::Texture TextureManager::GrassBlockTexture;
std::string TextureManager::RESOURCE_PATH = "../../resources/";
std::string TextureManager::BLOCK_PATH = TextureManager::RESOURCE_PATH + "blocks/";


using TM = TextureManager;

TextureManager::TextureManager()
{
    loadAllBlockTextures();
}

void TextureManager::loadAllBlockTextures()
{
    if (!TM::GrassBlockTexture.loadFromFile(TM::BLOCK_PATH + "grass_block.png")) {
        std::cerr << "FAILED TO LOAD GRASS BLOCK TEXTURE!" << std::endl;
    }
}
