#include "Game.h"

void Game::InitVariables() {
	/*
		@return void

		- initializeaza variabilele din joc
	*/

	this->_endGame = false;
	this->_window = nullptr;
}

void Game::InitWindow() {
	/*
		@return void

		- seteaza dimensiunea ferestrei in videoMode
		- initializeaza fereastra + error handling pentru fereastra
		- seteaza icon-ul jocului
		- seteaza framerate limit
	*/

	this->_videoMode = VideoMode(1080, 720);
	this->_window = new RenderWindow(this->_videoMode, "EcoSys", Style::Close | Style::Titlebar);

	if (this->_window == nullptr)
		Debug::Error("Fereastra nu s-a putut initializa corect.");
	else
		Debug::Loaded("Fereastra initializata cu succes.");

	this->SetWindowIcon(this->ICON_PATH);
	this->_window->setVerticalSyncEnabled(true);
}

void Game::SetWindowIcon(const string& fileName) {
	/*
		@return void

		- incarca icon-ul jocului intr-o imagine
		- verifica daca se incarca corect
		- seteaza icon-ul jocului
	*/
	
	if (!this->_windowIcon.loadFromFile(fileName))
		Debug::Error("Nu s-a putut incarca icon-ul pentru fereastra.");
	else Debug::Loaded("Icon incarcat cu succes.");

	Vector2u windowSize = this->_windowIcon.getSize();
	
	this->_window->setIcon(windowSize.x, windowSize.y, this->_windowIcon.getPixelsPtr());
}

void Game::InitMapConfigurator() {
	Vector2u mapSize = GetMapSize();

	this->_mapConfig = MapConfigurator(mapSize.x, mapSize.y, 5, MAP_CONFIG::PERLIN);
}

void Game::InitTileMap() {
	Vector2u mapSize = GetMapSize();

	this->_tileMap = TileMap(mapSize.x, mapSize.y);
	this->_tileMap.LoadTileMap(
		"tileSet.png",
		this->_mapConfig.GetMap(),
		this->TILE_SIZE,
		this->SCALING_FACTOR
	);
}

Game::Game() {
	this->InitVariables();
	this->InitWindow();
	this->InitMapConfigurator();
	this->InitTileMap();
}

Game::~Game() {
	delete this->_window;
}

const bool Game::GetWindowOpen() const {
	return this->_window->isOpen();
}

void Game::HandleInput() {
	while (this->_window->pollEvent(this->_ev)) {
		switch (this->_ev.type) {
		case Event::Closed:
			this->_window->close();
			break;
		case Event::KeyPressed:
			if (this->_ev.key.code == Keyboard::Escape)
				this->_window->close();
			if (this->_ev.key.code == Keyboard::Left) {
				this->BIAS -= 0.1f;
				cout << "BIAS: " << this->BIAS << '\n';
				this->_mapConfig.Update(this->OCTAVES, this->BIAS);
				this->_tileMap.Update(this->_mapConfig.GetMap());
			}
			if (this->_ev.key.code == Keyboard::Right) {
				this->BIAS += 0.1f;
				cout << "BIAS: " << this->BIAS << '\n';
				this->_mapConfig.Update(this->OCTAVES, this->BIAS);
				this->_tileMap.Update(this->_mapConfig.GetMap());
			}
			if (this->_ev.key.code == Keyboard::Space) {
				this->OCTAVES = (this->OCTAVES + 1) % 8;
				cout << "OCTAVES: " << this->OCTAVES << '\n';
				this->_mapConfig.Update(this->OCTAVES, this->BIAS);
				this->_tileMap.Update(this->_mapConfig.GetMap());
			}
			break;
		}
	}
}

Vector2u Game::GetMapSize() const {
	if (this->TILE_SIZE.x == 0 || this->TILE_SIZE.y == 0) {
		Debug::Error("GetMapSize() : impartire la TILE_SIZE = 0.");
		return Vector2u(0, 0);
	}

	Vector2u mapSize = Vector2u(
		this->_window->getSize().x / this->TILE_SIZE.x,
		this->_window->getSize().y / this->TILE_SIZE.y
	);

	return mapSize;
}

void Game::Update() {
	this->HandleInput();
}

void Game::Render() {
	this->_window->clear();

	this->_window->draw(this->_tileMap);

	this->_window->display();
}
