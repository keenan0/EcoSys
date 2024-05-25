#pragma once
#include "includes.h"

class Button {
private:
	sf::VertexArray button;
	sf::Texture texture;

	sf::Vector2f position;
	sf::Vector2f size;

	sf::Vector2u tileSize;
	sf::Vector2f textureScale;
public:
	Button() = default;

	Button(sf::Vector2f position, sf::Vector2f size, const std::string& filePath);

	~Button() = default;

	void Render(sf::RenderTarget* window);
	void Update(sf::Vector2f mousePos);

	//void SetTexture(const sf::Texture& texture) { this->texture = texture; };
	void SetPosition(sf::Vector2f position) { this->position = position; }
	void SetSize(sf::Vector2f size) { this->size = size; }

	[[nodiscard]] bool IsMouseOver(sf::Vector2f mousePos) const;
	Button& operator=(const Button& other) {
		if (this == &other)
			return *this;

		this->button = other.button;
		this->texture = other.texture;

		this->position = other.position;
		this->size = other.size;

		this->tileSize = other.tileSize;
		this->textureScale = other.textureScale;

		return *this;
	}
};