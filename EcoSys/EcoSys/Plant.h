#pragma once
#include "includes.h"
#include "Entity.h"

class Plant : public Entity {
public:
	int _visionAmount;
	int _healthAmount;

private:
	Plant();
	virtual ~Plant() override = default;


};

