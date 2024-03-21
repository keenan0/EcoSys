#pragma once
#include "includes.h"

class Entity {
private:
    Vector2f _position;

    TILE_TYPE _isOnTile;

    Texture _texture;
    Sprite _sprite;
public:
    Entity() {
        this->_isOnTile = TILE_TYPE::UNDEFINED;
        this->_position = Vector2f(0.0f, 0.0f);
    }

    Entity(Vector2f position) : _position(position), _isOnTile(TILE_TYPE::UNDEFINED) {}

    Entity(const Entity& toCopy) {
        this->_position = toCopy._position;
        this->_texture = toCopy._texture;
        this->_sprite = toCopy._sprite;
        this->_isOnTile = toCopy._isOnTile;
    }

    bool LoadTexture(string textureFileName) {
        if (!this->_texture.loadFromFile("img/" + textureFileName)) {
            cout << "Eroare: Nu s-a putut incarca fisierul: " << textureFileName << '\n';

            return false;
        }

        this->_sprite.setTexture(this->_texture);
        this->_sprite.setPosition(this->_position);
        return true;
    }

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