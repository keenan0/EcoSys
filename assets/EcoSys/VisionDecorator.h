#pragma once
#include "PlantDecorator.h"

class Animal;

class VisionDecorator : virtual public PlantDecorator {
public:
	VisionDecorator(Plant* plant) : PlantDecorator(plant) {}

	virtual void Consume(Animal* other) override;
};

