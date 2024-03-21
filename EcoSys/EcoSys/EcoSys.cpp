#include "Game.h"

int main() {
    srand(time(NULL));
    Game* ecosys = new Game;
    
    while (ecosys->GetWindowOpen()) {
        ecosys->Update();
        ecosys->Render();
    }
}

/*
case Event::MouseButtonPressed:
    if (event.mouseButton.button == Mouse::Left) {
        Vector2i mouse(event.mouseButton.x, event.mouseButton.y);
        Vector2i mapped(floor(mouse.x / TILE_SIZE.x / SCALING_FACTOR), floor(mouse.y / TILE_SIZE.y / SCALING_FACTOR));

        plants.emplace_back(Entity(Vector2f(mapped.x * TILE_SIZE.x * SCALING_FACTOR, mapped.y * TILE_SIZE.y * SCALING_FACTOR)));

        LoadTextures();
    }
*/