#pragma once
#include "Animal.h"

#include "Fox.h"
#include "Carrot.h"
#include "HelperFunctions.h"

class Rabbit : public Animal {
private:
	std::string rabbitTexture;

public:
	Rabbit() = default;
	Rabbit(const MapConfigurator& mapConfig);
	virtual ~Rabbit() = default;

	void Eat(Entity* other) override;
	virtual [[nodiscard]] sf::Vector2i GetNextPosition(const vector<Entity*> entities) override;	   

	//void Update(const vector<Entity*> entities);
};