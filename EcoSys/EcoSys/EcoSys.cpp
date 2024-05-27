#include "Entity.h"
#include "Game.h"
#include "AnimalFactoryConfig.h"

Game* Game::gameInstance = nullptr;
int Entity::incrementEntityId = 0;
vector<Entity*> Game::entities = {};

int main() {
    Game* ecosys = Game::GetInstance();
    
    while (ecosys->GetWindowOpen()) {
        ecosys->Update();
        ecosys->Render();
    }
}