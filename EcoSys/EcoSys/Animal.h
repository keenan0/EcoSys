#pragma once

#include "includes.h"
#include "Entity.h"

class Animal : public Entity {
private:
	int _health;

public:
	Animal() = default;
	virtual ~Animal() override = default;

	int GetHealth() const { return this->_health; }
};

