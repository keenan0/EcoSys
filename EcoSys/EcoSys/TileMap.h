#pragma once
#include "includes.h"

class TileMap : public Drawable, public Transformable {
private:
    Texture _texture;
    VertexArray _tileMapVertices;

    uint _width;
    uint _height;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    TileMap();
    ~TileMap() = default;

    TileMap(uint width, uint height);

    bool LoadTileMap(const string& tileMapTextureName, const int* tileConfig, Vector2u tileSize, float scalingFactor = 1.0f);
    void Update(const int* tileConfig, Vector2u tileSize = Vector2u(8,8), float scalingFactor = 1.0f);

    void SetWidth(const uint width) { this->_width = width; }
    void SetHeight(const uint height) { this->_height = height; }
};