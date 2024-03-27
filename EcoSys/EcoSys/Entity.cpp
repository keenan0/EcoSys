#include "Entity.h"

Vector2f Entity::MapTileCoords(Vector2i tileCoords) {
    return Vector2f(
        static_cast<float>(this->_tilePosition.x),
        static_cast<float>(this->_tilePosition.y)
    );
}

Entity::Entity() {
    this->_isOnTile = TILE_TYPE::UNDEFINED;
    this->_tilePosition = Vector2i(0, 0);
}

Entity::Entity(const Entity& toCopy) {
    this->_tilePosition = toCopy._tilePosition;
    this->_texture = toCopy._texture;
    this->_sprite = toCopy._sprite;
    this->_isOnTile = toCopy._isOnTile;
}

bool Entity::LoadTexture(const string& textureFileName) {
    /*
        @return bool

        - textureFileName = numele fisierului
        - functia deja include img/ in path
    */
    
    if (!this->_texture.loadFromFile("img/" + textureFileName)) {
        Debug::Error("Nu s - a putut incarca fisierul." + textureFileName);

        return false;
    }

    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(this->MapTileCoords(this->_tilePosition));
    return true;
}

Entity& Entity::operator=(const Entity& e) {
    this->_tilePosition = e._tilePosition;
    this->_sprite = e._sprite;
    this->_texture = e._texture;

    cout << "Avertizare: Entiate atribuita cu succes\n";

    return *this;
}

void Entity::Render(RenderWindow* currentWindow, const float scalingFactor) {
    if (this->_sprite.getTexture()) {
        this->_sprite.setScale(Vector2f(scalingFactor, scalingFactor));
        currentWindow->draw(this->_sprite);
    }
    else Debug::Error("Sprite is not initialised.");
}

void Entity::UpdateSprite(Vector2u tileSize, float scalingFactor) {
    this->_sprite.setPosition(Vector2f(
        static_cast<float>(this->_tilePosition.x * tileSize.x * scalingFactor),
        static_cast<float>(this->_tilePosition.y * tileSize.y * scalingFactor)
    ));
}
