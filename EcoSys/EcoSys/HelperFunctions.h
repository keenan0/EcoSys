#pragma once
#include "SFML/Graphics.hpp"

class HelperFunctions {
public:
	static [[nodiscard]] int MapVectot2iToInt(sf::Vector2i normalisedOffset) {
		if (normalisedOffset == sf::Vector2i(-1, -1)) { return 0; }
		if (normalisedOffset == sf::Vector2i(0, -1)) { return 1; }
		if (normalisedOffset == sf::Vector2i(1, -1)) { return 2; }
		if (normalisedOffset == sf::Vector2i(-1, 0)) { return 3; }
		if (normalisedOffset == sf::Vector2i(1, -1)) { return 4; }
		if (normalisedOffset == sf::Vector2i(-1, 1)) { return 5; }
		if (normalisedOffset == sf::Vector2i(0, 1)) { return 6; }
		if (normalisedOffset == sf::Vector2i(1, 1)) { return 7; }

		return 0;
	}

	static [[nodiscard]] sf::Vector2i MapIntToVector2i(int index) {
		if (index == 0) { return sf::Vector2i(-1, -1); }
		if (index == 1) { return sf::Vector2i(0, -1); }
		if (index == 2) { return sf::Vector2i(1, -1); }
		if (index == 3) { return sf::Vector2i(-1, 0); }
		if (index == 4) { return sf::Vector2i(1, -1); }
		if (index == 5) { return sf::Vector2i(-1, 1); }
		if (index == 6) { return sf::Vector2i(0, 1); }
		if (index == 7) { return sf::Vector2i(1, 1); }

		return sf::Vector2i(0, 0);
	}

	static [[nodiscard]] sf::Vector2i GetNeighbours(int index) {
		if (index == 0) { return sf::Vector2i(1, 3); }
		if (index == 1) { return sf::Vector2i(0, 2); }
		if (index == 2) { return sf::Vector2i(1, 4); }
		if (index == 3) { return sf::Vector2i(0, 5); }
		if (index == 4) { return sf::Vector2i(2, 7); }
		if (index == 5) { return sf::Vector2i(3, 6); }
		if (index == 6) { return sf::Vector2i(5, 7); }
		if (index == 7) { return sf::Vector2i(4, 6); }

		return sf::Vector2i(index, index);
	}
};

