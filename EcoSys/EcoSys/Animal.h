#pragma once

#include "includes.h"
#include "MapConfigurator.h"
#include "Entity.h"
#include "Carrot.h"

class Animal : public Entity {
protected:
	sf::Clock clock;
	float actionTime;

	int health;
	int visionRange;

	bool isMouseSelected;

	MapConfigurator mapConfig;
	sf::VertexArray visibleTilesVertices;
	vector<sf::Vector2i> visibleTileOffset;

	vector<Entity*> entitiesOnSameTile;

	void InitVariables();

	bool IsBounded(int x, int y, uint width, uint height) const;
	virtual [[nodiscard]] sf::Vector2i GetNextPosition(const vector<Entity*> entities);
	void ComputeTileOffsets();
	virtual void Wander(const vector<Entity*> entities);

	void GetEntitiesOnSameTile(const vector<Entity*> entities);

	void Behave();

public:
	Animal();
	Animal(const MapConfigurator& mapConfig);
	virtual ~Animal() override = default;

	void UpdateVisionRange(uint visionRange);

	void DisplayStats();
	void RenderVisibleTiles(sf::RenderTarget* target, const sf::Vector2u tileSize, const float scalingFactor);
	virtual void Update(const vector<Entity*> entities);
	void Render(sf::RenderWindow* currentWindow, const sf::Vector2u tileSize, const float scalingFactor) override;

	int GetHealth() const { return this->health; }
	bool GetMouseSelected() const { return this->isMouseSelected; }
	bool SwitchMouseSelected() { this->isMouseSelected = !this->isMouseSelected; };
	void SetActionTime(float actionTime);

	virtual void Eat(Entity*); //= 0;
};

