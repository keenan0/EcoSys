#include "TileSelector.h"

void TileSelector::InitVariables() {
	this->_mousePosWindow = Vector2i(0, 0);
	this->_mousePosView = Vector2f(0.f, 0.f);
	this->_tileCoords = Vector2i(0, 0);

	this->_outline = RectangleShape(Vector2f(
		(float)this->_tileSize.x * this->_scalingFactor, 
		(float)this->_tileSize.y * this->_scalingFactor
	));
	this->_outline.setFillColor(Color::Black);
	this->_outline.setPosition(Vector2f(0.f, 0.f));
}

TileSelector::TileSelector() {
	this->InitVariables();
}

void TileSelector::UpdateMouse(RenderWindow* target) {
	this->_mousePosWindow = Mouse::getPosition(*target);
	this->_mousePosView = target->mapPixelToCoords(this->_mousePosWindow);
}

Vector2i TileSelector::GetTileCoords() {
	Vector2i tileCoords = Vector2i(
		this->_mousePosWindow.x / this->_tileSize.x / this->_scalingFactor,
		this->_mousePosWindow.y / this->_tileSize.y / this->_scalingFactor
	);

	return tileCoords;	
}

void TileSelector::Debug() {
	cout << this->_tileCoords.x << ' ' << this->_tileCoords.y << '\n';
	cout << this->_mousePosView.x << ' ' << this->_mousePosView.y << '\n';
	cout << this->_outline.getPosition().x << ' ' << this->_outline.getPosition().y << '\n';
	cout << this->_outline.getSize().x << '\n';
}

void TileSelector::RenderTileOutline(RenderTarget* target) {
	this->_tileCoords = this->GetTileCoords();

	this->_outline.setPosition(
		(float)this->_tileCoords.x * this->_tileSize.x * this->_scalingFactor,
		(float)this->_tileCoords.y * this->_tileSize.x * this->_scalingFactor
	);

	target->draw(this->_outline);
	//this->Debug();
}

TileSelector::TileSelector(Vector2u tileSize, float scalingFactor) {
	this->_scalingFactor = scalingFactor;
	this->_tileSize = tileSize;
	
	this->InitVariables();
}

void TileSelector::UpdateVariables(Vector2u tileSize, float scalingFactor) {
	this->_scalingFactor = scalingFactor;
	this->_tileSize = tileSize;
}

void TileSelector::Update(RenderWindow* target) {
	this->UpdateMouse(target);
}

void TileSelector::Render(RenderTarget* target) {
	this->RenderTileOutline(target);
}
