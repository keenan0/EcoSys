#pragma once

#include "includes.h"

class Entity;
class Animal;

class TileSelector {
private:
	sf::Color _hover;
	sf::Color _click;
	sf::Color _error;

	sf::Vector2u _tileSize;
	float _scalingFactor;

	sf::Vector2i _mousePosWindow;
	sf::Vector2f _mousePosView;

	sf::Vector2i _tileCoords;

	sf::Texture _outlineTexture;
	sf::Sprite _outline;
	sf::Color _outlineColor;

	bool _isSelected;
	Entity* _selectedEntity;

	void InitVariables();
	void UpdateMouse(sf::RenderWindow* target);
	void RenderTileOutline(sf::RenderTarget* target);
	
	sf::Vector2i GetTileCoords(sf::RenderWindow* window);
	void Debug();
public:
	TileSelector();
	~TileSelector() = default;

	void HandleInput(sf::Event ev, std::vector<Entity*>& entities);
	void SetScalingFactor(float scalingFactor);
	void SetTileSize(sf::Vector2u tileSize);
	void SetSelectedEntity(Entity* entity);

	void UpdateVariables(sf::Vector2u tileSize, float scalingFactor);
	void Update(sf::RenderWindow* target);
	void Render(sf::RenderTarget* target);
};

