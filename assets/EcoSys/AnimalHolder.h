#pragma once
#include "includes.h"
#include "Rabbit.h"
#include "Fox.h"

template<typename T>
class AnimalHolder {
private:
	T animal;

public:
	AnimalHolder(const T& animal) : animal(animal) {};

	void DisplayStats() { this->animal->DisplayStats(); };

	template<typename U>
	bool AreSameType(const AnimalHolder<U>& other);
};

template<typename T>
template<typename U>
inline bool AnimalHolder<T>::AreSameType(const AnimalHolder<U>& other) {
	if (std::is_same_v<T, Rabbit*> && std::is_same_v<U, Rabbit*>) 
		return true;

	if (std::is_same_v<T, Fox*> && std::is_same_v<U, Fox*>) 
		return true;

	return false;
}
