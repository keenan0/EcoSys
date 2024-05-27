#include "SpeedDecorator.h"
#include "Animal.h"

void SpeedDecorator::Consume(Animal* other) {
	PlantDecorator::Consume(other);

	other->UpdateSpeed(-0.2f);
}
