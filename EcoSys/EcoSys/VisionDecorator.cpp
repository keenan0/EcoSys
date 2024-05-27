#include "VisionDecorator.h"
#include "Animal.h"

void VisionDecorator::Consume(Animal* other) {
	PlantDecorator::Consume(other);

	other->UpdateVisionRange(other->GetVisionRange() + 1);
}
