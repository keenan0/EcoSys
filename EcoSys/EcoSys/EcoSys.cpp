#include "Game.h"

int main() {
    srand(time(NULL));
    Game* ecosys = new Game;
    
    while (ecosys->GetWindowOpen()) {
        ecosys->Update();
        ecosys->Render();
    }
}