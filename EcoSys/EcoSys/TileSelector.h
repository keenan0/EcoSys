#pragma once

#include "includes.h"
#include "Entity.h"

class TileSelector {
private:
	Color _hover;
	Color _click;
	Color _error;

	Vector2u _tileSize;
	float _scalingFactor;

	Vector2i _mousePosWindow;
	Vector2f _mousePosView;

	Vector2i _tileCoords;

	Texture _outlineTexture;
	Sprite _outline;
	Color _outlineColor;

	bool _isSelected;

	Entity _selectedEntity;

	void InitVariables();
	void UpdateMouse(RenderWindow* target);
	void RenderTileOutline(RenderTarget* target);
	
	Vector2i GetTileCoords(RenderWindow* window);
	void Debug();
public:
	TileSelector();
	~TileSelector() = default;

	void HandleInput(Event ev);
	void SetScalingFactor(float scalingFactor);
	void SetTileSize(Vector2u tileSize);
	void UpdateVariables(Vector2u tileSize, float scalingFactor);
	void Update(RenderWindow* target);
	void Render(RenderTarget* target);
};

