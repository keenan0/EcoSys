#pragma once
#include "Plant.h"

class Animal;

class PlantDecorator : virtual public Plant {
protected:
	Plant* plant;

public:
	PlantDecorator() = default;
	PlantDecorator(Plant* plant) : plant(plant), Plant() {}
	~PlantDecorator() { delete this->plant; }

	virtual void Consume(Animal* other) override { this->plant->Consume(other); }
};
	
