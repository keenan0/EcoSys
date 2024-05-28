#include "AnimalFactoryConfig.h"

AnimalFactoryConfig::AnimalFactoryConfig(int minWidth, int maxWidth, int minHeight, int maxHeight, sf::Vector2i foxVision, sf::Vector2i rabbitVision, sf::Vector2f foxActionTime, sf::Vector2f rabbitActionTime, const MapConfigurator& map) {
	this->eng = std::mt19937(this->rd());

	this->widthDistr = std::uniform_int_distribution<>(minWidth, maxWidth);
	this->heightDistr = std::uniform_int_distribution<>(minHeight, maxHeight);

	this->foxVision = std::uniform_int_distribution<>(foxVision.x, foxVision.y);
	this->rabbitVision = std::uniform_int_distribution<>(rabbitVision.x, rabbitVision.y);

	this->foxActionTime = std::uniform_real_distribution<>(foxActionTime.x, foxActionTime.y);
	this->rabbitActionTime = std::uniform_real_distribution<>(rabbitActionTime.x, rabbitActionTime.y);

	this->map = map;
}
