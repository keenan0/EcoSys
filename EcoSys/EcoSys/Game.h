#pragma once

//#include "Animal.h"
//#include "Rabbit.h"
//#include "Fox.h"
//
//#include "Plant.h"
//#include "Carrot.h"

#include "MapConfigurator.h"
#include "TileMap.h"
#include "TileSelector.h"
#include "AnimalFactory.h"

#include "includes.h"

class Entity;
class Animal;
class Rabbit;
class Fox;

class Plant;
class Carrot;

class PlantDecorator;
class HealDecorator;
class SpeedDecorator;
class VisionDecorator;

/**
 * TODO.
 * 
 * - WASD camera movement should move one tile at a time
 * - Zooming out the camera should be bounded to the borders of the tilemap
 */

class Game {
private:
	Game();

	// Constants that could be put into a config file.
	// Singleton design pattern

	static Game* gameInstance;

	// The game's icon path
	const string ICON_PATH = "img/carrot.png";
	
	// The tile size that the game will be working with
	const sf::Vector2u TILE_SIZE = sf::Vector2u(8, 8);

	// How should the tiles be scaled. 
	const float SCALING_FACTOR = 2.f;
	
	/**
	 * Variables for testing purposes.
	 * 
	 * They decide the randomness of the map generation
	 */

	float BIAS = 0.4f;
	uint OCTAVES = 5;

	bool endGame;

	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Image windowIcon;
	sf::View mainView;

	sf::Event ev;

	TileSelector selector;
	MapConfigurator mapConfig;
	TileMap tileMap;

	// Entity variables 
	uint nEntities;

	//POLIMORPHISM
	static vector<Entity*> entities;

	std::random_device rd;

	// Private Functions
	void InitVariables();
	
	void InitWindow();
	void SetWindowIcon(const string& fileName);

	void InitMapConfigurator();
	void InitTileMap();
	void InitTileSelector();

	void InitEntities();

	void InitGui();
	void InitBackgroundGui();

	void HandleMouseSelectorInput();
	void MoveView();

	void RenderEntities();
	void UpdateEntities();

	void SpawnAnimals();
	void SpawnPlants();
public:
	~Game();

	static Game* GetInstance();

	void HandleInput();
	[[nodiscard]] const bool GetWindowOpen() const;
	[[nodiscard]] sf::Vector2u GetMapSize() const;

	static void deleteEntity(Entity* target);

	void Update();
	void Render();
};

