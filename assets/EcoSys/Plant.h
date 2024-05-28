#pragma once
#include "includes.h"
#include "Entity.h"

class Animal;

class Plant : public Entity {
protected:

public:
	Plant() = default;
	virtual ~Plant() override = default;

	virtual void Consume(Animal* other) = 0;
};

