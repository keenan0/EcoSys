#pragma once
#include "Plant.h"

class Carrot : public Plant {
private:
	std::string carrotTexture;

public:
	Carrot() : carrotTexture("carrot.png") {
		(this)->LoadTexture(this->carrotTexture);
	}
	~Carrot() = default;
};

