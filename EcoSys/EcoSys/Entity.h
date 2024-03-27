#pragma once
#include "includes.h"

class Entity {
protected:
    Vector2i _tilePosition;

    TILE_TYPE _isOnTile;

    Texture _texture;
    Sprite _sprite;

    Vector2f MapTileCoords(Vector2i tileCoords);
public:
    Entity();
    Entity(Vector2f position) : _tilePosition(position), _isOnTile(TILE_TYPE::WATER) {}
    Entity(const Entity& toCopy);
    virtual ~Entity() = default;

    bool LoadTexture(const string& textureFileName);
    
    void Render(RenderWindow* currentWindow, const float scalingFactor);
    void UpdateSprite(Vector2u tileSize, float scalingFactor);

    void SetPosition(Vector2i position) { this->_tilePosition = position; }
    void SetPosition(int x, int y) { this->_tilePosition = Vector2i(x, y); }
    Vector2i GetPosition() const { return this->_tilePosition; }

    Entity& operator=(const Entity& e);
};