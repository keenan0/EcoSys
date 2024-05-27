#pragma once
#include "enums.h"
#include "AnimalFactoryConfig.h"

class Animal;
class Rabbit;
class Fox;

class AnimalFactory {
private:
	AnimalFactoryConfig config;

public:
	AnimalFactory() = default;
	~AnimalFactory() = default;

	AnimalFactory(const AnimalFactoryConfig& config);

	Animal* GetAnimal(ANIMAL_FACTORY animalType);
};

