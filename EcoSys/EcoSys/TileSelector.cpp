#include "TileSelector.h"

void TileSelector::InitVariables() {
	this->_hover = Color(38, 38, 38, 255);
	this->_click = Color(35, 166, 35, 255);
	this->_error = Color(166, 35, 35, 255);
	this->_outlineColor = this->_error;

	this->_isSelected = true;
	
	if (!this->_outlineTexture.loadFromFile("img/outline.png"))
		Debug::Error("Outline-ul nu s-a incarcat corect.");

	this->_mousePosWindow = Vector2i(0, 0);
	this->_mousePosView = Vector2f(0.f, 0.f);
	this->_tileCoords = Vector2i(0, 0);

	this->_outline.setTexture(this->_outlineTexture);
	this->_outline.setColor(this->_outlineColor);
	this->_outline.setPosition(Vector2f(0.f, 0.f));
}

TileSelector::TileSelector() {
	this->InitVariables();
}

void TileSelector::UpdateMouse(RenderWindow* target) {
	this->_mousePosWindow = Mouse::getPosition(*target);
	this->_mousePosView = target->mapPixelToCoords(this->_mousePosWindow);
}

Vector2i TileSelector::GetTileCoords(RenderWindow* window) {
	//TODO: Inca nu stiu de ce nu merge cum vreau eu dar o las asa momentan
	
	/*
	
		@return Vector2i

		- returneaza coordonatele tile-ului in care se afla mouse-ul 
	*/

	View view = window->getView();

	Vector2f worldPos = this->_mousePosView;


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

	Vector2i tileCoords = Vector2i(
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

void TileSelector::HandleInput(Event ev) {
	if (ev.type == Event::KeyPressed) {
		if (ev.key.code == Keyboard::R) {
			this->_isSelected = !this->_isSelected;
		}
	}
}

void TileSelector::RenderTileOutline(RenderTarget* target) {
	if (this->_isSelected) {
		target->draw(this->_outline);
	}
}

void TileSelector::SetScalingFactor(float scalingFactor) {
	this->_scalingFactor = scalingFactor;

	this->_outline.setScale(this->_scalingFactor, this->_scalingFactor);
}

void TileSelector::SetTileSize(Vector2u tileSize) {
	this->_tileSize = tileSize;
}

void TileSelector::UpdateVariables(Vector2u tileSize, float scalingFactor) {
	this->_scalingFactor = scalingFactor;
	this->_tileSize = tileSize;
}

void TileSelector::Update(RenderWindow* target) {
	this->UpdateMouse(target);

	this->_tileCoords = this->GetTileCoords(target);

	this->_outline.setPosition(
		(float)this->_tileCoords.x * this->_tileSize.x * this->_scalingFactor,
		(float)this->_tileCoords.y * this->_tileSize.x * this->_scalingFactor
	);
}

void TileSelector::Render(RenderTarget* target) {
	this->RenderTileOutline(target);
}
