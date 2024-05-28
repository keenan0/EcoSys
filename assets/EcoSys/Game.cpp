#include "Game.h"
#include "Entity.h"
#include "Animal.h"
#include "Rabbit.h"
#include "Fox.h"
#include "Carrot.h"
#include "PlantDecorator.h"
#include "VisionDecorator.h"
#include "HealDecorator.h"
#include "SpeedDecorator.h"
#include "AnimalHolder.h"

Game::Game() {
	/**
	 * The game constructor initialises everything.
	 *
	 */

	this->InitVariables();
	this->InitWindow();
	this->InitMapConfigurator();
	this->InitTileMap();
	this->InitTileSelector();
	this->InitEntities();
	this->InitGui();
}

void Game::InitVariables() {
	/**
	 * Initialises all the game variables.
	 */

	this->endGame = false;
	this->window = nullptr;
	this->mainView = sf::View(sf::FloatRect(0, 0, 1080, 720));
	//this->guiView = sf::View(sf::FloatRect(0, 0, 1080, 720));
}

void Game::InitWindow() {
	/**
	 * Initialises the window of the game.
	 * 
	 * Sets the dimensions of the video mode
	 * Initialises the window and checks for errors
	 * Sets the icon 
	 * Sets the framerate limit
	 * Sets the views of the game
	 */
	
	this->videoMode = sf::VideoMode(1080, 720);
	this->window = new sf::RenderWindow(this->videoMode, "EcoSys", sf::Style::Close | sf::Style::Titlebar);

	if (this->window == nullptr)
		Debug::Error("Fereastra nu s-a putut initializa corect.");
	else
		Debug::Loaded("Fereastra initializata cu succes.");

	this->SetWindowIcon(this->ICON_PATH);
	this->window->setVerticalSyncEnabled(true);

	//this->mainView.setViewport(sf::FloatRect(0.1f, 0.f, 1.f, 1.f));
	//this->guiView.setViewport(sf::FloatRect(0.f, 0.f, 0.1f, 1.f));
	this->window->setView(this->mainView);
}

void Game::SetWindowIcon(const string& fileName) {
	/**
	 * Sets the window icon.
	 * 
	 * \param[in] fileName		The path to the icon image
	 * 
	 * Loads the icon into an image
	 * Handles errors
	 * If successful, it sets the window icon to the image
	 */
	
	// Can be replaced with exception handling
	if (!this->windowIcon.loadFromFile(fileName))
		Debug::Error("Nu s-a putut incarca icon-ul pentru fereastra.");
	else Debug::Loaded("Icon incarcat cu succes.");

	sf::Vector2u windowSize = this->windowIcon.getSize();
	
	this->window->setIcon(windowSize.x, windowSize.y, this->windowIcon.getPixelsPtr());
}

void Game::InitMapConfigurator() {
	/**
	 * Initialises the map configurator of the game.
	 * 
	 * The game only has one map configurator, which will generate a random map config for the tilemap
	 */

	sf::Vector2u mapSize = GetMapSize();

	this->mapConfig = MapConfigurator(mapSize.x, mapSize.y, 5, MAP_CONFIG::PERLIN);
	this->mapConfig.Update(this->OCTAVES, this->BIAS);
	this->tileMap.Update(this->mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
}

void Game::InitTileMap() {
	/**
	 * Intitialises the tile map of the game.
	 * 
	 * \throw		The path to the texture has to be without img/ because it is already included inside the code
	 */
	
	sf::Vector2u mapSize = GetMapSize();

	this->tileMap = TileMap(mapSize.x, mapSize.y);
	this->tileMap.LoadTileMap(
		"tileSet.png",
		this->mapConfig.GetMap(),
		this->TILE_SIZE,
		this->SCALING_FACTOR
	);
}

void Game::InitTileSelector() {
	/**
	 * Initialises the tile selector object.
	 * 
	 * Sets the tile selector tile size and scaling factor
	 */
	
	/*
		@return void

		- initializeaza tile selectorul cu dimensiunea unui tile si cu scaling factor ul potrivit
	*/
	
	this->selector.SetScalingFactor(this->SCALING_FACTOR);
	this->selector.SetTileSize(this->TILE_SIZE);
}

void Game::InitEntities() {
	/**
	 * Initialises the entities inside the game.
	 */

	// FOR DEBUGGING CARROT
	/*this->entities.push_back(new Carrot());
	this->entities[this->entities.size() - 1]->SetPosition(4,4);*/

	std::uniform_int_distribution<> animalType(0, ANIMAL_FACTORY::SIZE);

	this->SpawnAnimals();
	this->SpawnPlants();
}

void Game::SpawnAnimals() {
	AnimalFactoryConfig config(
		0, this->mapConfig.GetWidth(),
		0, this->mapConfig.GetHeight(),
		sf::Vector2i(4, 7),
		sf::Vector2i(2, 4),
		sf::Vector2f(1.2f, 1.5f),
		sf::Vector2f(0.8f, 1.2f),
		this->mapConfig
	);

	int nRabbits = 30;
	int nFoxes = 30;

	AnimalFactory animalSpawner(config);
	for (int i = 0; i < nRabbits; ++i)
		this->entities.push_back(animalSpawner.GetAnimal(ANIMAL_FACTORY::RABBIT));

	for (int i = 0; i < nFoxes; ++i)
		this->entities.push_back(animalSpawner.GetAnimal(ANIMAL_FACTORY::FOX));

	for (const auto& animal : this->entities) {
		if (Rabbit* rabbit = dynamic_cast<Rabbit*>(animal)) {
			AnimalHolder<Rabbit*> myRabbit(rabbit);
			myRabbit.DisplayStats();
		}
		else if (Fox* fox = dynamic_cast<Fox*>(animal)) {
			AnimalHolder<Fox*> myFox(fox);
			myFox.DisplayStats();
		}
	}
}

void Game::SpawnPlants() {
	Plant* myPlant = new Carrot();
	
	//myPlant = new HealDecorator(myPlant);
	/*myPlant = new SpeedDecorator(myPlant);
	myPlant = new VisionDecorator(myPlant);
	*/
	

	myPlant->SetPosition(5, 5);
	this->entities.push_back(myPlant);
}

void Game::InitGui() {
	/**
	 * Initialises the GUI elements (buttons, textures etc...).
	 * 
	 */
	
	/*this->backgroundColor = sf::Color(190, 100, 18);
	this->InitBackgroundGui();

	sf::Vector2f pos = sf::Vector2f(0.f, 0.f);
	sf::Vector2f size = sf::Vector2f(40.f, 40.f);

	this->playButton = Button(pos, size, "play.png");*/
}

void Game::HandleMouseSelectorInput() {
	/**
	 * Controller for the map configurator.
	 * 
	 * By pressing any of the ARROW LEFT | ARROW RIGHT, the bias of the configurator will change and the tilemap will be updated
	 * 
	 * Also, by pressing space, the number of octaves is increased, making the generation of the map config smoother
	 */

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->BIAS -= 0.1f;
		std::cout << "BIAS: " << this->BIAS << '\n';
		this->mapConfig.Update(this->OCTAVES, this->BIAS);
		this->tileMap.Update(this->mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->BIAS += 0.1f;
		std::cout << "BIAS: " << this->BIAS << '\n';
		this->mapConfig.Update(this->OCTAVES, this->BIAS);
		this->tileMap.Update(this->mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->OCTAVES = (this->OCTAVES + 1) % 8;
		std::cout << "OCTAVES: " << this->OCTAVES << '\n';
		this->mapConfig.Update(this->OCTAVES, this->BIAS);
		this->tileMap.Update(this->mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}
}

void Game::MoveView() {
	/**
	 * Moves the view and binds the camera to a FloatRect.
	 * 
	 * \brief		+ To be added
	 */

	sf::Vector2f moveDir;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveDir.y = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveDir.y = 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveDir.x = -1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveDir.x = 1.f;
	}


	// Normalises the moveDir vector to prevent faster moving on the diagonals
	/*float length = std::sqrt(moveDir.x * moveDir.x + moveDir.y * moveDir.y);

	if (length) {
		moveDir.x /= length;
		moveDir.y /= length;
	}*/

	// Upscales the moveDir vector with TileSize * ScalingFactor
	moveDir = sf::Vector2f(
		moveDir.x * this->TILE_SIZE.x * this->SCALING_FACTOR,
		moveDir.y * this->TILE_SIZE.y * this->SCALING_FACTOR
	);

	std::cout << "center: " << mainView.getCenter().x << ' ' << mainView.getCenter().y << '\n';
	std::cout << "size: " << mainView.getSize().x << '\n';
	// New pos is the next position that has to be checked
	sf::Vector2f newPos = this->mainView.getCenter() + moveDir;

	/*sf::Vector2f topLeft = 
		this->mainView.getCenter() - 
		sf::Vector2f(
			this->mainView.getSize().x / 2,
			this->mainView.getSize().y / 2
		);

	sf::Vector2f bottomRight =
		this->mainView.getCenter() +
		sf::Vector2f(
			this->mainView.getSize().x / 2,
			this->mainView.getSize().y / 2
		);*/

	sf::Vector2f topLeft = sf::Vector2f(0.f, 0.f);
	sf::Vector2f bottomRight = sf::Vector2f(972, 720);

	std::cout << newPos.x << ' ' << newPos.y << '\n';

	float worldLeft = topLeft.x;
	float worldTop = topLeft.y;
	float worldWidth = bottomRight.x;
	float worldHeight = bottomRight.y;

	std::cout << "left: " << worldLeft << '\n';
	std::cout << "top: " << worldTop << '\n';
	std::cout << "width: " << worldWidth << '\n';
	std::cout << "height: " << worldHeight << '\n';
	std::cout << '\n';
	
	if (newPos.x - this->mainView.getSize().x / 2 >= worldLeft &&
		newPos.x + this->mainView.getSize().x / 2 <= worldLeft + worldWidth &&
		newPos.y - this->mainView.getSize().y / 2 >= worldTop &&
		newPos.y + this->mainView.getSize().y / 2 <= worldTop + worldHeight)
	{
		this->mainView.move(moveDir);
	}
}

void Game::InitBackgroundGui() {
	/*this->background = sf::VertexArray(sf::Quads, 4);

	this->background[0].position = sf::Vector2f(0.f, 0.f);
	this->background[1].position = sf::Vector2f(1080.f, 0.f);
	this->background[2].position = sf::Vector2f(1080.f, 720.f);
	this->background[3].position = sf::Vector2f(0.f, 720.f);

	this->background[0].color = this->backgroundColor;
	this->background[1].color = this->backgroundColor;
	this->background[2].color = this->backgroundColor;
	this->background[3].color = this->backgroundColor;*/
}

void Game::RenderEntities() {
	/**
	 * Renders all entities in the game.
	 * 
	 * Calls the render function for each entity
	 */

	for (int i = 0; i < this->entities.size(); ++i) {
		if (this->entities[i] == nullptr) continue;

		dynamic_cast<Entity*>(this->entities[i])->Render(this->window, this->TILE_SIZE, this->SCALING_FACTOR);
	}
}

void Game::UpdateEntities() {
	/**
	 * Updates all the entities in the game.
	 * 
	 * Calls the UpdateSprite function for each entity and sets the tilePosition accordingly
	 * Calls the Update function for each entity
	 */
	
	for (int i = 0; i < this->entities.size(); ++i) {
		if (this->entities[i] == nullptr) continue;
		
		this->entities[i]->UpdateSprite(this->TILE_SIZE, this->SCALING_FACTOR);

		if(Animal* animal = dynamic_cast<Animal*>(this->entities[i]))
			animal->Update(this->entities);

		/*if (Rabbit* rabbit = dynamic_cast<Rabbit*>(entities[i])) {
			rabbit->Update(this->entities);
		}
		else if(Animal* animal = dynamic_cast<Animal*>(this->entities[i])){
			animal->Update(this->entities);
		}
		else if (Fox* fox = dynamic_cast<Fox*>(this->entities[i])) {
			fox->Update(this->entities);
		}*/
	}
}

Game* Game::GetInstance() {
	if (gameInstance == nullptr) {
		gameInstance = new Game();
	}

	return gameInstance;
}

void Game::HandleInput() {
	while (this->window->pollEvent(this->ev)) {
		this->selector.HandleInput(this->ev, this->entities);

		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			this->HandleMouseSelectorInput();
			this->MoveView();
			this->window->setView(this->mainView);
			break;
		case sf::Event::MouseWheelScrolled:
			if (this->ev.mouseWheelScroll.delta < 0) {	
				std::cout << "Scroll down: \n";
				this->mainView.zoom(2.f);
			}
			else if (this->ev.mouseWheelScroll.delta > 0) {
				std::cout << "Scroll up: \n";
				this->mainView.zoom(0.5f);
			}
			
			this->window->setView(this->mainView);

			break;
		}
	}

}

void Game::Update() {
	/**
	 * Function that handles input and updates everything in the game.
	 */

	//First handle the input
	this->HandleInput();

	// All entities must be updated here
	this->UpdateEntities();
	
	this->selector.Update(this->window);


	// Update the GUI
	sf::Vector2i mousePosi = sf::Mouse::getPosition(*this->window);
	sf::Vector2f mousePos = sf::Vector2f(
		static_cast<float>(mousePosi.x),
		static_cast<float>(mousePosi.y)
	);

	//sf::Vector2f mouse = sf::Vector2f(this->window->mapCoordsToPixel(mousePos, this->guiView).x, this->window->mapCoordsToPixel(mousePos, this->guiView).y);
	//this->playButton.Update(this->window->mapPixelToCoords(sf::Mouse::getPosition()));
}

void Game::Render() {
	/**
	 * Renders every drawable object to the window.
	 */

	// First the window is cleared
	this->window->clear();

	this->window->setView(this->mainView);
	// Then the tilemap is drawn
	this->window->draw(this->tileMap);
	// Then the selector, which is part of the GUI
	this->selector.Render(this->window);
	
	// Then the entities are rendered
	this->RenderEntities();


	// !!!!!!!!!!!!!!!!!!!!!!!! GUI
	// Render the GUI
	//this->window->setView(this->guiView);

	// Draw the GUI here
	//this->window->draw(this->background);
	//this->playButton.Render(this->window);



	// Reset the view
	//this->window->setView(this->mainView);
	// And lastly, the window is displayed after the frame is drawn
	this->window->display();
}

Game::~Game() {
	delete this->window;
}

[[nodiscard]] const bool Game::GetWindowOpen() const {
	return this->window->isOpen();
}

[[nodiscard]] sf::Vector2u Game::GetMapSize() const {
	/**
	 * Returns the tilemap size as a vector (x,y).
	 * 
	 * \return sf::Vector2u
	 */

	try {
		sf::Vector2u mapSize = sf::Vector2u(
			this->window->getSize().x / this->TILE_SIZE.x / this->SCALING_FACTOR,
			this->window->getSize().y / this->TILE_SIZE.y / this->SCALING_FACTOR
		);

		return mapSize;
	}
	catch (const std::exception& e) {
		Debug::Error("GetMapSize() : impartire la 0.");
	}

	return sf::Vector2u(0, 0);
}

void Game::deleteEntity(Entity* target) {
	int targetId = target->GetEntityId();
	
	for (int i = 0; i < entities.size(); ++i){
		if (entities[i]->GetEntityId() == targetId) {
			entities.erase(entities.begin() + i);
		}
	}
}
