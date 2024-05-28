#pragma once
#include "includes.h"

class Entity {
protected:
    static int incrementEntityId;
    int entityId;

    sf::Vector2i _tilePosition;

    TILE_TYPE _isOnTile;

    sf::Texture _texture;
    sf::Sprite _sprite;

    sf::Vector2f MapTileCoords(sf::Vector2i tileCoords);
public:
    Entity();
    Entity(sf::Vector2f position) : _tilePosition(position), _isOnTile(TILE_TYPE::WATER) {
        this->entityId = ++incrementEntityId;
    }
    Entity(const Entity& toCopy);
    virtual ~Entity() = default;

    bool LoadTexture(const string& textureFileName);
    void Move(sf::Vector2i delta);

    virtual void Render(sf::RenderWindow* currentWindow, const sf::Vector2u tileSize, const float scalingFactor);
    void UpdateSprite(sf::Vector2u tileSize, float scalingFactor);

    // Getters and setters
    void SetPosition(sf::Vector2i position) { this->_tilePosition = position; }
    void SetPosition(int x, int y) { this->_tilePosition = sf::Vector2i(x, y); }
    sf::Vector2i GetPosition() const { return this->_tilePosition; }

    int GetEntityId() { return this->entityId; }

    Entity& operator=(const Entity& e);
};