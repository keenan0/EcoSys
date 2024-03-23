#pragma once

#include "includes.h"

class TileSelector {
private:
	Vector2u _tileSize;
	float _scalingFactor;

	Vector2i _mousePosWindow;
	Vector2f _mousePosView;

	Vector2i _tileCoords;

	RectangleShape _outline;

	void InitVariables();
	void UpdateMouse(RenderWindow* target);
	void RenderTileOutline(RenderTarget* target);
	
	Vector2i GetTileCoords();
	void Debug();
public:
	TileSelector();
	~TileSelector() = default;

	TileSelector(Vector2u tileSize, float scalingFactor);

	void UpdateVariables(Vector2u tileSize, float scalingFactor);
	void Update(RenderWindow* target);
	void Render(RenderTarget* target);
};

