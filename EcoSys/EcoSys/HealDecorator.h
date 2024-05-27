#pragma once
#include "PlantDecorator.h"

class Animal;

class HealDecorator : virtual public PlantDecorator {
public:
    HealDecorator(Plant* plant) : PlantDecorator(plant) {}

    virtual void Consume(Animal* other) override;
};

