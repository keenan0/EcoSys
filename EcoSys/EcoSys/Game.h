#pragma once

#include "MapConfigurator.h"
#include "TileMap.h"
#include "TileSelector.h"

#include "includes.h"

class Game {
private:
	//~CONSTANTE CARE AR PUTEA FI INCARCATE DINTR-UN CONFIG

	//Path-ul spre icon-ul jocului
	const string ICON_PATH = "img/carrot.png";
	
	//Dimensiunea fiecarui tile din textura
	const Vector2u TILE_SIZE = Vector2u(8, 8);

	//Cat de mari sa fie randate tileuri-le
	//Posibil sa nu mai fie nevoie de ea
	const float SCALING_FACTOR = 1.5f;

	//*****TEMPORAR PENTRU TESTARE
	float BIAS = 2.0f;
	uint OCTAVES = 4;

	//~VARIABILE PRIVATE
	bool _endGame;

	VideoMode _videoMode;
	RenderWindow* _window;
	Image _windowIcon;
	View _mainView;

	Event _ev;

	TileSelector _selector;
	MapConfigurator _mapConfig;
	TileMap _tileMap;

	//TEMPORAR PENTRU A VERIFICA CUM SE ADAUGA O ENTITATE (CARROT)
	Entity* _carrot;

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
public:
	Game();
	~Game();

	const bool GetWindowOpen() const;
	void HandleInput();
	Vector2u GetMapSize() const;

	void Update();
	void Render();
};

