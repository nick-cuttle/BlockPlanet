#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextureManager {

public:

    static std::string RESOURCE_PATH;
    static std::string BLOCK_PATH;
    
    static sf::Texture GrassBlockTexture;
    TextureManager();

private:

    void loadAllBlockTextures();

public:



};