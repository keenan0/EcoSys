#pragma once
#include "Animal.h"

class Rabbit;

class Fox : public Animal {
private:
	std::string foxTexture;

public:
	Fox() = default;
	Fox(const MapConfigurator& mapConfig);
	virtual ~Fox() = default;

	void Eat(Entity* other) override;
	virtual [[nodiscard]] sf::Vector2i GetNextPosition(const vector<Entity*> entities) override;
};

