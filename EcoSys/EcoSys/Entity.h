#pragma once
#include "includes.h"

class Entity {
private:
    Vector2f _position;

    TILE_TYPE _isOnTile;

    Texture _texture;
    Sprite _sprite;
public:
    Entity();
    Entity(Vector2f position) : _position(position), _isOnTile(TILE_TYPE::WATER) {}

    Entity(const Entity& toCopy);

    bool LoadTexture(const string& textureFileName);

    void DrawSprite(RenderWindow& currentWindow) {
        //this->_sprite.setScale(Vector2f(SCALING_FACTOR, SCALING_FACTOR));

        currentWindow.draw(this->_sprite);
    }

    Vector2f getPosition() const { return this->_position; }

    ~Entity() {
        cout << "Avertisment: Entitate distrusa!\n";
    }

    Entity& operator=(const Entity& e) {
        this->_position = e._position;
        this->_sprite = e._sprite;
        this->_texture = e._texture;

        cout << "Avertizare: Entiate atribuita cu succes\n";

        return *this;
    }
};