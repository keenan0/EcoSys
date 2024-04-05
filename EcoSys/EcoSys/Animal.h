#pragma once

#include "includes.h"
#include "MapConfigurator.h"
#include "Entity.h"

class Animal : public Entity {
private:
	sf::Clock clock;
	float actionTime;

	int health;
	int visionRange;

	bool isMouseSelected;

	MapConfigurator mapConfig;
	sf::VertexArray visibleTilesVertices;
	vector<sf::Vector2i> visibleTileOffset;

	void InitVariables();

	bool IsBounded(int x, int y, uint width, uint height) const;
	sf::Vector2i GetNextPosition();
	void ComputeTileOffsets();
	void Wander();
public:
	Animal();
	Animal(const MapConfigurator& mapConfig);
	virtual ~Animal() override = default;

	void UpdateVisionRange(uint visionRange);

	void DisplayStats();
	void RenderVisibleTiles(sf::RenderTarget* target, const sf::Vector2u tileSize, const float scalingFactor);
	void Update();
	void Render(sf::RenderWindow* currentWindow, const sf::Vector2u tileSize, const float scalingFactor) override;

	int GetHealth() const { return this->health; }
	bool GetMouseSelected() const { return this->isMouseSelected; }
	bool SwitchMouseSelected() { this->isMouseSelected = !this->isMouseSelected; };
	void SetActionTime(float actionTime);
};

