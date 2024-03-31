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

	void RenderVisibleTiles(sf::RenderTarget* target, const sf::Vector2u tileSize, const float scalingFactor);
	void Update();
	//virtual void Render(RenderWindow* currentWindow, const float scalingFactor) override;

	int GetHealth() const { return this->health; }
	void SetActionTime(float actionTime);
};

