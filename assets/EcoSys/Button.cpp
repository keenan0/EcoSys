#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, const std::string& filePath) : position(position), size(size) {
	//this->texture = new sf::Texture();
	
	this->button = sf::VertexArray(sf::Quads, 4);
	
	this->button[0].position = position; // top left
	this->button[1].position = sf::Vector2f(
		position.x + size.x,
		position.y
	); // top right
	this->button[2].position = sf::Vector2f(
		position.x + size.x,
		position.y + size.y
	); // bottom right
	this->button[3].position = sf::Vector2f(
		position.x,
		position.y + size.y
 	); // bottom left

	if (!this->texture.loadFromFile("img/" + filePath)) {
		Debug::Error("Could not open play button texture.");
	}

	this->tileSize = this->texture.getSize();
	this->textureScale = sf::Vector2f(
		size.x / this->tileSize.x,
		size.y / this->tileSize.y
	);

	this->button[0].texCoords = sf::Vector2f(0.f, 0.f);

	this->button[1].texCoords = sf::Vector2f(
		static_cast<float>(this->tileSize.x),
		0.f
	);

	this->button[2].texCoords = sf::Vector2f(
		static_cast<float>(this->tileSize.x),
		static_cast<float>(this->tileSize.y)
	);

	this->button[3].texCoords = sf::Vector2f(
		0.f,
		static_cast<float>(this->tileSize.y)
	);
}

void Button::Render(sf::RenderTarget* window) {
	window->draw(this->button, &this->texture);
}

void Button::Update(sf::Vector2f mousePos) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->IsMouseOver(mousePos)) {
			cout << "Clicked the button at pos: ";

			cout << mousePos.x << ' ' << mousePos.y << '\n';
		}
	}
}

bool Button::IsMouseOver(sf::Vector2f mousePos) const {
	return (mousePos.x >= this->position.x && mousePos.x <= this->position.x + this->size.x && this->position.y + this->size.y >= mousePos.y && mousePos.y >= this->position.y);
}

