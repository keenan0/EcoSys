#include "HealDecorator.h"
#include "Animal.h"

void HealDecorator::Consume(Animal* other) {
    PlantDecorator::Consume(other);

    other->Heal(1);
}
