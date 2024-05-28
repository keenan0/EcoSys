#include "Fox.h"
#include "Fox.h"
#include "Rabbit.h"

#include "HelperFunctions.h"

Fox::Fox(const MapConfigurator& mapConfig) : Animal(mapConfig), foxTexture("fox.png") {
	this->LoadTexture(this->foxTexture);
}

void Fox::Eat(Entity* other) {
	if (Rabbit* rabbit = dynamic_cast<Rabbit*>(other)) {
		cout << "I ATE A RABBIT!\n";

		Game::deleteEntity(rabbit);
	}
	else if (Carrot* carrot = dynamic_cast<Carrot*>(other)) {
		cout << "ATE CARROT\n";
		this->UpdateVisionRange(this->visionRange + 1);

		Game::deleteEntity(carrot);
	}
}

sf::Vector2i Fox::GetNextPosition(const vector<Entity*> entities) {
	sf::Vector2i curr = this->_tilePosition;
	const int* map = this->mapConfig.GetMap();

	uint width = this->mapConfig.GetWidth();
	uint height = this->mapConfig.GetHeight();

	vector<sf::Vector2i> possibleMoves;
	vector<float> movingChance(8);
	for (int i = 0; i < movingChance.size(); ++i) movingChance[i] = 0.f;

	for (sf::Vector2i offset : this->visibleTileOffset) {
		sf::Vector2i current = offset + curr;

		for (Entity* entity : entities) {
			if (entity->GetPosition().x == current.x && entity->GetPosition().y == current.y) {
				sf::Vector2i normalisedOffset;

				if (offset.x == 0 && offset.y == 0) {
					normalisedOffset = sf::Vector2i(
						0,
						0
					);
				}
				else if (offset.x == 0) {
					normalisedOffset = sf::Vector2i(
						0,
						offset.y / abs(offset.y)
					);
				}
				else if (offset.y == 0) {
					normalisedOffset = sf::Vector2i(
						offset.x / abs(offset.x),
						0
					);
				}
				else {
					normalisedOffset = sf::Vector2i(
						offset.x / abs(offset.x),
						offset.y / abs(offset.y)
					);
				}

				float points = 0.f;
				if (Fox* fox = dynamic_cast<Fox*>(entity)) {
					points = 8.f;
					cout << "Added 5 points for friend fox.\n";
				}
				else if (Carrot* carrot = dynamic_cast<Carrot*>(entity)) {
					points = 5.f;
					cout << "Added 5 points for food fox.\n";
				}
				else if (Rabbit* rabbit = dynamic_cast<Rabbit*>(entity)) {
					points = 30.f;
					cout << "SAW RABBIT EAT  HIM\n";
				}

				//cout << "Normalised offset: " << normalisedOffset.x << ' ' << normalisedOffset.y << '\n';
				movingChance[HelperFunctions::MapVectot2iToInt(normalisedOffset)] += points;
			}
		}
	}

	vector<float> movingChanceAux(8);
	// Smoothen out the values
	for (int ii = -1; ii <= 1; ++ii) {
		for (int jj = -1; jj <= 1; ++jj) {
			if (ii == 0 && jj == 0) continue;
			else {
				int index = HelperFunctions::MapVectot2iToInt(sf::Vector2i(jj, ii));

				// Less than an epsilon
				if (abs(movingChance[index]) < 0.05f) {
					sf::Vector2i neigh = HelperFunctions::GetNeighbours(index);

					movingChanceAux[index] = (movingChance[neigh.x] + movingChance[neigh.y]) / 2;
				}
				else {
					movingChanceAux[index] = movingChance[index];
				}
			}
		}
	}

	// Pick the maximum value to move towards
	float maxVal = movingChanceAux[0];
	int maxIndex = 0;

	for (int i = 1; i < 8; ++i) {
		if (movingChanceAux[i] > maxVal)
			maxVal = movingChanceAux[i], maxIndex = i;
	}

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (this->IsBounded(curr.x + j, curr.y + i, width, height)) {
				if (i == 0 && j == 0) continue;
				else {
					TILE_TYPE currentTileType = (TILE_TYPE)(map[(i + curr.y) * width + (curr.x + j)]);

					if (currentTileType == TILE_TYPE::WATER) { continue; }
					else {
						float diff = abs(movingChanceAux[HelperFunctions::MapVectot2iToInt(sf::Vector2i(j, i))] - maxVal);
						float epsilon = 0.1f;

						if (diff < epsilon) {
							possibleMoves.push_back(sf::Vector2i(j, i));
						}
					}
				}
			}
		}
	}

	if (possibleMoves.size() == 0)
		return sf::Vector2i(0, 0);

	std::mt19937 eng(rd());
	std::uniform_int_distribution<> index(0, possibleMoves.size());

	return possibleMoves[index(eng) % possibleMoves.size()];
}
