#include "Game.h"

int main() {
    Game* ecosys = new Game;
    
    while (ecosys->GetWindowOpen()) {
        ecosys->Update();
        ecosys->Render();
    }
}