#pragma once

#include "MapConfigurator.h"
#include "TileMap.h"
#include "TileSelector.h"
#include "Animal.h"
#include "Plant.h"

#include "includes.h"

class Game {
private:
	//~CONSTANTE CARE AR PUTEA FI INCARCATE DINTR-UN CONFIG

	//Path-ul spre icon-ul jocului
	const string ICON_PATH = "img/carrot.png";
	
	//Dimensiunea fiecarui tile din textura
	const sf::Vector2u TILE_SIZE = sf::Vector2u(8, 8);

	//Cat de mari sa fie randate tileuri-le
	//Posibil sa nu mai fie nevoie de ea
	const float SCALING_FACTOR = 2.f;

	//*****TEMPORAR PENTRU TESTARE
	float BIAS = 0.5f;
	uint OCTAVES = 5;

	//~VARIABILE PRIVATE
	bool _endGame;

	sf::VideoMode _videoMode;
	sf::RenderWindow* _window;
	sf::Image _windowIcon;
	sf::View _mainView;

	sf::Event _ev;

	TileSelector _selector;
	MapConfigurator _mapConfig;
	TileMap _tileMap;

	//TEMPORAR PENTRU A VERIFICA CUM SE ADAUGA O ENTITATE (CARROT)
	Entity* _carrot;
	Entity* _rabbit;

	vector<Entity*> entities;
	uint nEntities;

	std::random_device rd;

	//~FUNCTII PRIVATE
	void InitVariables();
	
	void InitWindow();
	void SetWindowIcon(const string& fileName);

	void InitMapConfigurator();
	void InitTileMap();
	void InitTileSelector();

	void InitEntities();

	void HandleMouseSelectorInput();
	void MoveView();

	void RenderEntities();
	void UpdateEntities();
public:
	Game();
	~Game();

	const bool GetWindowOpen() const;
	void HandleInput();
	sf::Vector2u GetMapSize() const;

	void Update();
	void Render();
};

