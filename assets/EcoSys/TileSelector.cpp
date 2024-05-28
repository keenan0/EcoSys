#include "TileSelector.h"
#include "Animal.h"
#include "Entity.h"

TileSelector::TileSelector() {
	this->InitVariables();
}

void TileSelector::InitVariables() {
	this->_hover = sf::Color(38, 38, 38, 255);
	this->_click = sf::Color(35, 166, 35, 255);
	this->_error = sf::Color(166, 35, 35, 255);
	this->_outlineColor = this->_hover;

	this->_isSelected = true;
	
	if (!this->_outlineTexture.loadFromFile("img/outline.png"))
		Debug::Error("Outline-ul nu s-a incarcat corect.");

	this->_selectedEntity = nullptr;
	this->_mousePosWindow = sf::Vector2i(0, 0);
	this->_mousePosView = sf::Vector2f(0.f, 0.f);
	this->_tileCoords = sf::Vector2i(0, 0);

	this->_outline.setTexture(this->_outlineTexture);
	this->_outline.setColor(this->_outlineColor);
	this->_outline.setPosition(sf::Vector2f(0.f, 0.f));
}

void TileSelector::UpdateMouse(sf::RenderWindow* target) {
	this->_mousePosWindow = sf::Mouse::getPosition(*target);
	this->_mousePosView = target->mapPixelToCoords(this->_mousePosWindow);
}

sf::Vector2i TileSelector::GetTileCoords(sf::RenderWindow* window) {
	//TODO: Inca nu stiu de ce nu merge cum vreau eu dar o las asa momentan
	
	/*
	
		@return Vector2i

		- returneaza coordonatele tile-ului in care se afla mouse-ul 
	*/

	sf::View view = window->getView();

	sf::Vector2f worldPos = this->_mousePosView;


	/*
	Posibil o alta implementare?
	
	Vector2f viewPos = view.getCenter() - view.getSize() / 2.0f;
	Vector2f scale(
		view.getSize().x / window->getDefaultView().getSize().x,
		view.getSize().y / window->getDefaultView().getSize().y
	);
	
	cout << "Size:" << viewPos.x << ' ' << viewPos.y << '\n';

	worldPos = Vector2f(
		(worldPos.x - viewPos.x) / scale.x,
		(worldPos.y - viewPos.y) / scale.y
	);
	
	*/

	sf::Vector2i tileCoords = sf::Vector2i(
		worldPos.x / this->_tileSize.x / this->_scalingFactor,
		worldPos.y / this->_tileSize.y / this->_scalingFactor
	);

	return tileCoords;	
}

void TileSelector::Debug() {
	/*cout << "Tile Coords" << this->_tileCoords.x << ' ' << this->_tileCoords.y << '\n';
	cout << "Mouse: " << this->_mousePosView.x << ' ' << this->_mousePosView.y << '\n';
	cout << "POS: " << this->_outline.getPosition().x << ' ' << this->_outline.getPosition().y << '\n';*/
	cout << "SIZE: " << this->_outline.getGlobalBounds().width << ' ' << this->_outline.getGlobalBounds().height << '\n';
	cout << "TEXTURE SIZE: " << this->_outlineTexture.getSize().x << ' ' << this->_outlineTexture.getSize().y << '\n';
}

void TileSelector::HandleInput(sf::Event ev, std::vector<Entity*>& entities) {
	if (ev.type == sf::Event::KeyPressed) {
		if (ev.key.code == sf::Keyboard::R) {
			this->_isSelected = !this->_isSelected;
		}
	}
	if (this->_isSelected) {
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left)
				this->_isSelected = false;
			cout << this->_tileCoords.x << ' ' << this->_tileCoords.y << '\n';
		}
	}
	else {
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (ev.mouseButton.button == sf::Mouse::Left) {
				//If the left mouse button is pressed go through each entity in the game and see if the mouseTilePos is the same as the entity tile position
	
				for (int i = 0; i < entities.size(); ++i) {
					//Cannot add or remove entities
					if (this->_tileCoords == entities[i]->GetPosition()) {
						cout << "CLICK" << entities[i]->GetPosition().x << ' ' << entities[i]->GetPosition().y << '\n';
						this->_selectedEntity = entities[i];
						this->_isSelected = true;
					}
				}
			}
		}
	}
}



void TileSelector::RenderTileOutline(sf::RenderTarget* target) {
	if (this->_isSelected) {
		target->draw(this->_outline);
	}
}

void TileSelector::SetScalingFactor(float scalingFactor) {
	this->_scalingFactor = scalingFactor;

	this->_outline.setScale(this->_scalingFactor, this->_scalingFactor);
}

void TileSelector::SetTileSize(sf::Vector2u tileSize) {
	this->_tileSize = tileSize;
}

void TileSelector::UpdateVariables(sf::Vector2u tileSize, float scalingFactor) {
	this->_scalingFactor = scalingFactor;
	this->_tileSize = tileSize;
}

void TileSelector::Update(sf::RenderWindow* target) {
	this->UpdateMouse(target);
	
	if (!this->_isSelected) {
		this->_selectedEntity = nullptr;
	}

	this->_tileCoords = this->GetTileCoords(target);

	this->_outline.setPosition(
		(float)this->_tileCoords.x * this->_tileSize.x * this->_scalingFactor,
		(float)this->_tileCoords.y * this->_tileSize.x * this->_scalingFactor
	);
}

void TileSelector::Render(sf::RenderTarget* target) {
	this->RenderTileOutline(target);

	if (this->_selectedEntity) {
		dynamic_cast<Animal*>(this->_selectedEntity)->RenderVisibleTiles(target, this->_tileSize, this->_scalingFactor);
		dynamic_cast<Animal*>(this->_selectedEntity)->DisplayStats();
	}
}


void TileSelector::SetSelectedEntity(Entity* entity) {
	this->_selectedEntity = entity;
	std::cout << "Called\n";
}
