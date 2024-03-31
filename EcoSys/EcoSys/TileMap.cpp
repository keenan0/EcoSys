#include "TileMap.h"

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &this->_texture;

    target.draw(this->_tileMapVertices, states);
}

TileMap::TileMap() {
    this->_width = 0;
    this->_height = 0;
}

TileMap::TileMap(uint width, uint height) {
    this->_width = width;
    this->_height = height;
}

bool TileMap::LoadTileMap(const string& tileMapTextureName, const int* tileConfig, sf::Vector2u tileSize, float scalingFactor) {
    /*
        @return bool

        - functia incarca o textura in memorie
        - initializeaza vectorul de vertexuri cu dimensiunea potrivita
        - pentru fiecare quad (tile) din map config, seteaza pozitia corecta si textura fiecarui vertex in functie de valoarea din map config
    */
        

    if (!this->_texture.loadFromFile("img/" + tileMapTextureName)) {
        Debug::Error("Nu s-a putut incarca textura pentru tilemap.");

        return false;
    }

    this->_tileMapVertices.setPrimitiveType(sf::PrimitiveType::Quads);
    this->_tileMapVertices.resize(this->_width * this->_height * 4);

    for (int i = 0; i < this->_width; ++i) {
        for (int j = 0; j < this->_height; ++j) {
            int tileNumber = tileConfig[i + j * this->_width];
            int nTilesInTextureRow = this->_texture.getSize().x / tileSize.x;

            int textureX = tileNumber % nTilesInTextureRow;
            int textureY = tileNumber / nTilesInTextureRow;

            sf::Vertex* quad = &this->_tileMapVertices[(i + j * this->_width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y) * scalingFactor;
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y) * scalingFactor;
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y) * scalingFactor;
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y) * scalingFactor;

            quad[0].texCoords = sf::Vector2f(textureX * tileSize.x, textureY * tileSize.y);
            quad[1].texCoords = sf::Vector2f((textureX + 1) * tileSize.x, textureY * tileSize.y);
            quad[2].texCoords = sf::Vector2f((textureX + 1) * tileSize.x, (textureY + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(textureX * tileSize.x, (textureY + 1) * tileSize.y);
        }
    }

    return true;
}

void TileMap::Update(const int* tileConfig, sf::Vector2u tileSize, float scalingFactor) {
    this->_tileMapVertices.setPrimitiveType(sf::PrimitiveType::Quads);
    this->_tileMapVertices.resize(this->_width * this->_height * 4);

    for (int i = 0; i < this->_width; ++i) {
        for (int j = 0; j < this->_height; ++j) {
            int tileNumber = tileConfig[i + j * this->_width];
            int nTilesInTextureRow = this->_texture.getSize().x / tileSize.x;

            int textureX = tileNumber % nTilesInTextureRow;
            int textureY = tileNumber / nTilesInTextureRow;

            sf::Vertex* quad = &this->_tileMapVertices[(i + j * this->_width) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y) * scalingFactor;
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y) * scalingFactor;
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y) * scalingFactor;
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y) * scalingFactor;

            quad[0].texCoords = sf::Vector2f(textureX * tileSize.x, textureY * tileSize.y);
            quad[1].texCoords = sf::Vector2f((textureX + 1) * tileSize.x, textureY * tileSize.y);
            quad[2].texCoords = sf::Vector2f((textureX + 1) * tileSize.x, (textureY + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(textureX * tileSize.x, (textureY + 1) * tileSize.y);
        }
    }
}

