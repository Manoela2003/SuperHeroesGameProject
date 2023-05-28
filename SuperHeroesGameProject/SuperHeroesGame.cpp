#include "SuperHeroesGame.h"

bool SuperHeroesGame::AddAdministrator(const Administrator& other) {
	if (IndexOfloggedInAdmin != -1) {
		administrators.AddElement(new Administrator(other));
		return true;
	}
	return false;
}

bool SuperHeroesGame::AddPlayer(const Player& other) {
	if (IndexOfloggedInAdmin != -1) {
		players.AddElement(new Player(other));
		return true;
	}
	return false;
}

bool SuperHeroesGame::DeletePlayer(const char* username) {
	if (!username)
		throw std::invalid_argument("The username doesn't exist");

	if (IndexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can delete players!");

	for (int i = 0; i < players.GetCount(); i++) {
		if (!strcmp(players[i]->GetUsername(), username)) {
			players.RemoveElement(i);
			return true;
		}
	}
	return false;
}
