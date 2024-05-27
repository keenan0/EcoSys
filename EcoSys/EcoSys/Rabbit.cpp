#include "Rabbit.h"

Rabbit::Rabbit(const MapConfigurator& mapConfig) : Animal(mapConfig), rabbitTexture("rabbit.png") { 
	this->LoadTexture(this->rabbitTexture);
}

void Rabbit::Eat(Entity* other) {
	if (Carrot* carrot = dynamic_cast<Carrot*>(other)) {
		this->UpdateVisionRange(this->visionRange + 1);
		cout << "I ate a carrot\n";

		Game::deleteEntity(carrot);
	}
}

sf::Vector2i Rabbit::GetNextPosition(const vector<Entity*> entities) {
	sf::Vector2i curr = this->_tilePosition;
	const int* map = this->mapConfig.GetMap();

	uint width = this->mapConfig.GetWidth();
	uint height = this->mapConfig.GetHeight();

	vector<sf::Vector2i> possibleMoves;
	vector<float> movingChance(8);
	for (int i = 0; i < movingChance.size(); ++i) movingChance[i] = 0.f;

	for (auto& offset : this->visibleTileOffset) {
		//cout << offset.x << ' ' << offset.y << '\n';
	}

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
			
				// From (5, -3) -> (1, -1) 

				/*
					0   1   2
					3	R   4
					5   6   7

					2 will be affected
				*/

				//What type of entity is this?

				float points = 0.f;
				if (Rabbit* rabbit = dynamic_cast<Rabbit*>(entity)) {
					points = 5.f;
					cout << "Added 5 points for friend.\n";
				} else if (Carrot* carrot = dynamic_cast<Carrot*>(entity)) {
					points = 15.f;
					cout << "Added 15 points for food.\n";
				}
				else if (Fox* fox = dynamic_cast<Fox*>(entity)) {
					points = -30.f;
					cout << "Saw fox, run.\n";
				}
				cout << "Normalised offset: " << normalisedOffset.x << ' ' << normalisedOffset.y << '\n';
				movingChance[HelperFunctions::MapVectot2iToInt(normalisedOffset)] += points;
			}
		}
	}

	/*cout << "Sanse: \n";
	int idx = 0;
	for (int ii = -1; ii <= 1; ++ii) {
		for (int jj = -1; jj <= 1; ++jj) {
			if (ii == 0 && jj == 0) cout << "  ";
			else cout << movingChance[idx++] << ' ';
		}

		cout << '\n';
	}*/

	//TO DO:
	// CHANGE THE UNIFORMIZATION MODEL

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

	/*cout << "Sanse uniforme: \n";
	idx = 0;
	for (int ii = -1; ii <= 1; ++ii) {
		for (int jj = -1; jj <= 1; ++jj) {
			if (ii == 0 && jj == 0) cout << "  ";
			else cout << movingChanceAux[idx++] << ' ';
		}

		cout << '\n';
	}
	cout << '\n';*/

	// Pick the maximum value to move towards
	float maxVal = movingChanceAux[0];
	int maxIndex = 0;

	for (int i = 1; i < 8; ++i) {
		if (movingChanceAux[i] > maxVal)
			maxVal = movingChanceAux[i], maxIndex = i;
	}

	//return HelperFunctions::MapIntToVector2i(maxIndex);

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (this->IsBounded(curr.x + j, curr.y + i, width, height)) {
				if (i == 0 && j == 0) continue;
				else {
					TILE_TYPE currentTileType = (TILE_TYPE)(map[(i + curr.y) * width + (curr.x + j)]);

					if (currentTileType == TILE_TYPE::WATER) { continue; }
					else { 
						// If the offset we are checking is equal to the maxValue found, add it to the possibleMoves
						// The checking has to be done using the x - y < epsilon because we are comparing floats

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

//void Rabbit::Update(const vector<Entity*> entities) {
//	/*
//		@return void
//
//		- Update function for the animal
//		- Uses the internal animal clock to update the animal position, stats, etc.
//	*/
//	this->ComputeTileOffsets();
//
//	sf::Time elapsedTime = this->clock.getElapsedTime();
//
//	if (elapsedTime.asSeconds() > this->actionTime) {
//		this->clock.restart();
//
//		this->Wander(entities);
//	}
//}
