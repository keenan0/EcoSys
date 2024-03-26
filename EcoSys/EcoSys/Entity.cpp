#include "Entity.h"

Entity::Entity() {
    this->_isOnTile = TILE_TYPE::WATER;
    this->_position = Vector2f(0.0f, 0.0f);
}

Entity::Entity(const Entity& toCopy) {
    this->_position = toCopy._position;
    this->_texture = toCopy._texture;
    this->_sprite = toCopy._sprite;
    this->_isOnTile = toCopy._isOnTile;
}

bool Entity::LoadTexture(const string& textureFileName) {
    if (!this->_texture.loadFromFile("img/" + textureFileName)) {
        Debug::Error("Nu s - a putut incarca fisierul." + textureFileName);

        return false;
    }

    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(this->_position);
    return true;
}