#pragma once
#include "includes.h"
#include "MapConfigurator.h"

struct AnimalFactoryConfig {
public:
	std::random_device rd;
	std::mt19937 eng;

	std::uniform_int_distribution<> widthDistr;
	std::uniform_int_distribution<> heightDistr;
	
	std::uniform_int_distribution<> nFox;
	std::uniform_int_distribution<> nRabbit;

	std::uniform_int_distribution<> foxVision;
	std::uniform_int_distribution<> rabbitVision;

	std::uniform_real_distribution<> foxActionTime;
	std::uniform_real_distribution<> rabbitActionTime;

	MapConfigurator map;

	AnimalFactoryConfig() = default;
	AnimalFactoryConfig(int foxes, int nRabbit, int minWidth, int maxWidth, int minHeight, int maxHeight, sf::Vector2i foxVision, sf::Vector2i rabbitVision, sf::Vector2f foxActionTime, sf::Vector2f rabbitActionTime, const MapConfigurator& map);
	~AnimalFactoryConfig() = default;
};

