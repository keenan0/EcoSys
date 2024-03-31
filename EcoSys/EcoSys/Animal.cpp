#include "Animal.h"

Animal::Animal() {
	/*
		@Animal constructor

		[required] mapConfig

		- The function will throw an error because a mapConfig is [required].
	*/

	Entity();
	Debug::Warning("Animal initialised without MapConfigurator.");
	this->InitVariables();
}

Animal::Animal(const MapConfigurator& mapConfig) {
	/*
		@Animal constructor

		[required] mapConfig

		- The mapConfig is necessary in order to get access to the tilemap width and height, and even the tile codes of the map
	*/

	this->mapConfig = mapConfig;
	Debug::Loaded("Animal loaded successfully.");
	this->InitVariables();
}

void Animal::InitVariables() {
	/*
		@return void

		- Initialises the variables of the animal
		- Is called in each constructor
	*/

	this->health = 10;
	this->actionTime = 0.2f;
	this->clock.restart();

	this->UpdateVisionRange(2);
}

bool Animal::IsBounded(int x, int y,uint width, uint height) const {
	/*
		@return bool

		- Checks if a given tile position is valid or not
		- Used in computing the tile offset
	*/

	if (x < 0 || x > width || y < 0 || y > height)
		return false;

	return true;
}

sf::Vector2i Animal::GetNextPosition() {
	sf::Vector2i curr = this->_tilePosition;
	const int* map = this->mapConfig.GetMap();

	uint width = this->mapConfig.GetWidth();
	uint height = this->mapConfig.GetHeight();

	vector<sf::Vector2i> possibleMoves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (this->IsBounded(curr.x + j, curr.y + i, width, height)) {
				if (i == 0 && j == 0) continue;
				else {
					TILE_TYPE currentTileType = (TILE_TYPE)(map[(i + curr.y) * width + (curr.x + j)]);

					if (currentTileType == TILE_TYPE::WATER) { continue; }
					else { possibleMoves.push_back(sf::Vector2i(j, i)); }
				}
			}
		}
	}

	if (possibleMoves.size() == 0)
		return sf::Vector2i(0, 0);

	return possibleMoves[rand() % possibleMoves.size()];
}

void Animal::Wander() {
	sf::Vector2i moveDir = this->GetNextPosition();

	this->Move(moveDir);
}

void Animal::ComputeTileOffsets() {
	/*
		@return void
		- The function will take a map configurator as a parameter and compute the tiles that are visible to the animal using the visionRange
		- The offsets, represented as pairs of (x,y) coordinates, will be stored in the visibleTileOffset vector to be used later in rendering and other computations
	*/
	
	// First we clear the offset vector
	this->visibleTileOffset.clear();

	sf::Vector2i currentPos = this->_tilePosition;

	uint mapWidth = mapConfig.GetWidth();
	uint mapHeight = mapConfig.GetHeight();
	const int* temp = mapConfig.GetMap();

	// Then we add the new offset positions
	// TODO: Can be done more efficiently but in a later version

	for (int i = 0; i <= this->visionRange; ++i) {
		for (int j = -this->visionRange + i; j <= this->visionRange - i; ++j) {
			sf::Vector2i newPos = sf::Vector2i(
				currentPos.x + j,
				currentPos.y + i
			);

			sf::Vector2i newPos2 = sf::Vector2i(
				currentPos.x + j,
				currentPos.y - i
			);

			if (i == 0) {
				if (j == 0) continue;
				else {
					if (IsBounded(newPos.x, newPos.y, mapWidth, mapHeight)) {
						this->visibleTileOffset.push_back(sf::Vector2i(j, i));
					}
				}
			}
			else {
				if (IsBounded(newPos.x, newPos.y, mapWidth, mapHeight)) {
					this->visibleTileOffset.push_back(sf::Vector2i(j, i));
				}

				if (IsBounded(newPos2.x, newPos2.y, mapWidth, mapHeight)) {
					this->visibleTileOffset.push_back(sf::Vector2i(j, -i));
				}
			}
		}
	}
}

void Animal::UpdateVisionRange(uint visionRange) {
	/*
		@return void

		- Changes the visionRange
		- Recomputes the visionTleOffset vector because tiles will either be removed or added
	*/

	this->visionRange = visionRange;

	this->ComputeTileOffsets();
}

void Animal::RenderVisibleTiles(sf::RenderTarget* target, const sf::Vector2u tileSize, const float scalingFactor) {
	/*
		@return void

		- Renders the visible tiles using a vertexArray
	*/

	this->visibleTilesVertices.setPrimitiveType(sf::PrimitiveType::Quads);
	this->visibleTilesVertices.resize(this->visibleTileOffset.size() * 4);

	for (int i = 0; i < this->visibleTileOffset.size(); ++i) {
		sf::Vertex* quad = &this->visibleTilesVertices[i * 4];

		sf::Vector2f curr = sf::Vector2f(
			static_cast<float>(this->_tilePosition.x + this->visibleTileOffset[i].x),
			static_cast<float>(this->_tilePosition.y + this->visibleTileOffset[i].y)
		);

		sf::Vector2f offset = sf::Vector2f(
			1.f,
			1.f
		);

		quad[0].position = sf::Vector2f(
			curr.x * tileSize.x,
			curr.y * tileSize.y
		) * scalingFactor;

		quad[1].position = sf::Vector2f(
			(curr.x + offset.x) * tileSize.x,
			curr.y * tileSize.y
		) * scalingFactor;

		quad[2].position = sf::Vector2f(
			(curr.x + offset.x) * tileSize.x,
			(curr.y + offset.y) * tileSize.y
		) * scalingFactor;
		
		quad[3].position = sf::Vector2f(
			curr.x * tileSize.x,
			(curr.y + offset.y) * tileSize.y
		) * scalingFactor;
		
		quad[0].color = quad[1].color = quad[2].color = quad[3].color = sf::Color(0, 166, 0, 100);
	}

	target->draw(this->visibleTilesVertices);
}


void Animal::Update() {
	/*
		@return void

		- Update function for the animal
		- Uses the internal animal clock to update the animal position, stats, etc.
	*/

	sf::Time elapsedTime = this->clock.getElapsedTime();

	if (elapsedTime.asSeconds() > this->actionTime) {
		this->clock.restart();

		this->Wander();
		//this->GetNextPosition();
	}
}

void Animal::SetActionTime(float actionTime) {
	/*
		@params

		actionTime - Float that represents the number of seconds it will take to update the animal
	*/

	this->actionTime = actionTime;
}

