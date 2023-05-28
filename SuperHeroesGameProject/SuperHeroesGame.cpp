#include "SuperHeroesGame.h"

void SuperHeroesGame::AddAdministrator(const Administrator& other) {
	administrators.AddElement(new Administrator(other));
}

void SuperHeroesGame::AddPlayer(const Player& other){
	players.AddElement(new Player(other));
}
