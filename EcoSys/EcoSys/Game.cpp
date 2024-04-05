#include "Game.h"

void Game::InitVariables() {
	/*
		@return void

		- initializeaza variabilele din joc
	*/

	this->_endGame = false;
	this->_window = nullptr;
	this->_mainView = sf::View(sf::FloatRect(0, 0, 1080, 720));
}

void Game::InitWindow() {
	/*
		@return void

		- seteaza dimensiunea ferestrei in videoMode
		- initializeaza fereastra + error handling pentru fereastra
		- seteaza icon-ul jocului
		- seteaza framerate limit
	*/

	this->_videoMode = sf::VideoMode(1080, 720);
	this->_window = new sf::RenderWindow(this->_videoMode, "EcoSys", sf::Style::Close | sf::Style::Titlebar);

	if (this->_window == nullptr)
		Debug::Error("Fereastra nu s-a putut initializa corect.");
	else
		Debug::Loaded("Fereastra initializata cu succes.");

	this->SetWindowIcon(this->ICON_PATH);
	this->_window->setVerticalSyncEnabled(true);

	this->_mainView.setViewport(sf::FloatRect(0.1f, 0.f, 1.f, 1.f));

	this->_window->setView(this->_mainView);
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

	sf::Vector2u windowSize = this->_windowIcon.getSize();
	
	this->_window->setIcon(windowSize.x, windowSize.y, this->_windowIcon.getPixelsPtr());
}

void Game::InitMapConfigurator() {
	sf::Vector2u mapSize = GetMapSize();

	this->_mapConfig = MapConfigurator(mapSize.x, mapSize.y, 5, MAP_CONFIG::PERLIN);
}

void Game::InitTileMap() {
	/*
		@return void
		 
		- initializeaza tilemap-ul 
		- calea spre textura trebuie sa fie fara img/ (e deja inclus in constructor)
	*/

	sf::Vector2u mapSize = GetMapSize();

	this->_tileMap = TileMap(mapSize.x, mapSize.y);
	this->_tileMap.LoadTileMap(
		"tileSet.png",
		this->_mapConfig.GetMap(),
		this->TILE_SIZE,
		this->SCALING_FACTOR
	);
}

void Game::InitTileSelector() {
	/*
		@return void

		- initializeaza tile selectorul cu dimensiunea unui tile si cu scaling factor ul potrivit
	*/
	//this->_selector = TileSelector(this->entities);
	this->_selector.SetScalingFactor(this->SCALING_FACTOR);
	this->_selector.SetTileSize(this->TILE_SIZE);
}

void Game::InitEntities() {
	/*
		@return void
	*/
	this->nEntities = 4;

	std::mt19937 eng(rd());
	std::uniform_int_distribution<> widthDistr(0, this->_mapConfig.GetWidth());
	std::uniform_int_distribution<> heightDistr(0, this->_mapConfig.GetHeight());
	std::uniform_int_distribution<> vision(1, 5);
	std::uniform_real_distribution<> actionTime(0.1f, 1.5f);

	for (int i = 0; i < nEntities; ++i) {
		this->entities.push_back(new Animal(this->_mapConfig));

		this->entities[i]->LoadTexture("rabbit.png");
		
		int x = widthDistr(eng);
		int y = heightDistr(eng);

		this->entities[i]->SetPosition(x, y);

		dynamic_cast<Animal*>(this->entities[i])->UpdateVisionRange(vision(eng));
		dynamic_cast<Animal*>(this->entities[i])->SetActionTime(actionTime(eng));
	}

	this->_carrot = new Entity();
	this->_carrot->LoadTexture("carrot.png");
	this->_carrot->SetPosition(15, 20);

	//this->_rabbit = new Animal(this->_mapConfig);
	//this->_rabbit->LoadTexture("rabbit.png");
	//this->_rabbit->SetPosition(5,5);
	//dynamic_cast<Animal*>(this->_rabbit)->UpdateVisionRange(2);
}

void Game::HandleMouseSelectorInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->BIAS -= 0.1f;
		cout << "BIAS: " << this->BIAS << '\n';
		this->_mapConfig.Update(this->OCTAVES, this->BIAS);
		this->_tileMap.Update(this->_mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->BIAS += 0.1f;
		cout << "BIAS: " << this->BIAS << '\n';
		this->_mapConfig.Update(this->OCTAVES, this->BIAS);
		this->_tileMap.Update(this->_mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->OCTAVES = (this->OCTAVES + 1) % 8;
		cout << "OCTAVES: " << this->OCTAVES << '\n';
		this->_mapConfig.Update(this->OCTAVES, this->BIAS);
		this->_tileMap.Update(this->_mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}
	
	/*if (this->_ev.key.code == Keyboard::Left) {
		this->BIAS -= 0.1f;
		cout << "BIAS: " << this->BIAS << '\n';
		this->_mapConfig.Update(this->OCTAVES, this->BIAS);
		this->_tileMap.Update(this->_mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}
	if (this->_ev.key.code == Keyboard::Right) {
		this->BIAS += 0.1f;
		cout << "BIAS: " << this->BIAS << '\n';
		this->_mapConfig.Update(this->OCTAVES, this->BIAS);
		this->_tileMap.Update(this->_mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}
	if (this->_ev.key.code == Keyboard::Space) {
		this->OCTAVES = (this->OCTAVES + 1) % 8;
		cout << "OCTAVES: " << this->OCTAVES << '\n';
		this->_mapConfig.Update(this->OCTAVES, this->BIAS);
		this->_tileMap.Update(this->_mapConfig.GetMap(), this->TILE_SIZE, this->SCALING_FACTOR);
	}*/
}

void Game::MoveView() {
	switch (this->_ev.type) {
	case sf::Event::KeyPressed:
		if (this->_ev.key.code == sf::Keyboard::W) {
			this->_mainView.move(0.f, -static_cast<float>(this->TILE_SIZE.y) * this->SCALING_FACTOR);
		}
		if (this->_ev.key.code == sf::Keyboard::S) {
			this->_mainView.move(0.f, static_cast<float>(this->TILE_SIZE.y) * this->SCALING_FACTOR);
		}
		if (this->_ev.key.code == sf::Keyboard::A) {
			this->_mainView.move(-static_cast<float>(this->TILE_SIZE.y) * this->SCALING_FACTOR, 0.f);
		}
		if (this->_ev.key.code == sf::Keyboard::D) {
			this->_mainView.move(static_cast<float>(this->TILE_SIZE.y) * this->SCALING_FACTOR, 0.f);
		}
	}
}

void Game::RenderEntities() {
	for (int i = 0; i < this->nEntities; ++i) {
		this->entities[i]->Render(this->_window, this->TILE_SIZE, this->SCALING_FACTOR);
	}

	this->_carrot->Render(this->_window, this->TILE_SIZE, this->SCALING_FACTOR);
	//this->_rabbit->Render(this->_window, this->TILE_SIZE, this->SCALING_FACTOR);
}

void Game::UpdateEntities() {
	for (int i = 0; i < this->nEntities; ++i) {
		this->entities[i]->UpdateSprite(this->TILE_SIZE, this->SCALING_FACTOR);
		dynamic_cast<Animal*>(this->entities[i])->Update();
	}

	this->_carrot->UpdateSprite(this->TILE_SIZE, this->SCALING_FACTOR);
	//this->_rabbit->UpdateSprite(this->TILE_SIZE, this->SCALING_FACTOR);

	//dynamic_cast<Animal*>(this->_rabbit)->Update();
}
	
Game::Game() {
	this->InitVariables();
	this->InitWindow();
	this->InitMapConfigurator();
	this->InitTileMap();
	this->InitTileSelector();
	this->InitEntities();
}

void Game::HandleInput() {
	while (this->_window->pollEvent(this->_ev)) {
		this->_selector.HandleInput(this->_ev, this->entities);

		switch (this->_ev.type) {
		case sf::Event::Closed:
			this->_window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->_ev.key.code == sf::Keyboard::Escape)
				this->_window->close();
			this->HandleMouseSelectorInput();
			this->MoveView();
			this->_window->setView(this->_mainView);
			break;
		case sf::Event::MouseWheelScrolled:
			if (this->_ev.mouseWheelScroll.delta < 0) {	
				cout << "Scroll down: \n";
				this->_mainView.zoom(2.f);
			}
			else if (this->_ev.mouseWheelScroll.delta > 0) {
				cout << "Scroll up: \n";
				this->_mainView.zoom(0.5f);
			}
			
			this->_window->setView(this->_mainView);

			break;
		}
	}

}

void Game::Update() {
	this->HandleInput();

	//Toate entitatile trebuie updatate aici

	this->UpdateEntities();
	
	//this->_selector.SetSelectedEntity(*this->_carrot);
	this->_selector.Update(this->_window);
}

void Game::Render() {
	//Order matters here

	this->_window->clear();
	this->_window->draw(this->_tileMap);
	this->_selector.Render(this->_window);
	
	this->RenderEntities();

	this->_window->display();
}

Game::~Game() {
	delete this->_window;
}

const bool Game::GetWindowOpen() const {
	return this->_window->isOpen();
}

sf::Vector2u Game::GetMapSize() const {
	if (this->TILE_SIZE.x == 0 || this->TILE_SIZE.y == 0) {
		Debug::Error("GetMapSize() : impartire la TILE_SIZE = 0.");
		return sf::Vector2u(0, 0);
	}

	sf::Vector2u mapSize = sf::Vector2u(
		this->_window->getSize().x / this->TILE_SIZE.x / this->SCALING_FACTOR,
		this->_window->getSize().y / this->TILE_SIZE.y / this->SCALING_FACTOR
	);

	return mapSize;
}