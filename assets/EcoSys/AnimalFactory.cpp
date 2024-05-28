#include "AnimalFactory.h"

#include "Animal.h"
#include "Rabbit.h"
#include "Fox.h"

AnimalFactory::AnimalFactory(const AnimalFactoryConfig& other) {
	this->config.eng = std::mt19937(this->config.rd());

	this->config.widthDistr = other.widthDistr;
	this->config.heightDistr = other.heightDistr;

	this->config.foxVision = other.foxVision;
	this->config.rabbitVision = other.rabbitVision;

	this->config.foxActionTime = other.foxActionTime;
	this->config.rabbitActionTime = other.rabbitActionTime;

	this->config.map = other.map;
}

Animal* AnimalFactory::GetAnimal(ANIMAL_FACTORY animalType) {

	if (animalType == ANIMAL_FACTORY::RABBIT) {
		Rabbit* rabbit = new Rabbit(this->config.map);
		
		rabbit->SetPosition(
			this->config.widthDistr(this->config.eng),
			this->config.heightDistr(this->config.eng)
		);

		rabbit->UpdateVisionRange(this->config.rabbitVision(this->config.eng));

		rabbit->SetActionTime(this->config.rabbitActionTime(this->config.eng));

		return rabbit;
	}
	else if (animalType == ANIMAL_FACTORY::FOX) {
		Fox* fox = new Fox(this->config.map);

		fox->SetPosition(
			this->config.widthDistr(this->config.eng),
			this->config.heightDistr(this->config.eng)
		);

		fox->UpdateVisionRange(this->config.foxVision(this->config.eng));

		fox->SetActionTime(this->config.foxActionTime(this->config.eng));

		return fox;
	}

	Debug::Error("Returned null pointer.");
	return nullptr;
}
