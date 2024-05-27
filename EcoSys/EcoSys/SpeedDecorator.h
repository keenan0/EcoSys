#pragma once
#include "PlantDecorator.h"

class Animal;

class SpeedDecorator : public PlantDecorator {
public:
	SpeedDecorator(Plant* plant) : PlantDecorator(plant) {}

	virtual void Consume(Animal* other) override;
};

