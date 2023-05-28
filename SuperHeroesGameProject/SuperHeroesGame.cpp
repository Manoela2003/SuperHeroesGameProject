#include "SuperHeroesGame.h"

bool SuperHeroesGame::LogInAsAdministrator(const char* username, const char* password) const {
	if (!username || !password)
		throw std::invalid_argument("The username or password doesn't exist");

	for (int i = 0; i < administrators.GetCount(); i++) {
		if (!strcmp(administrators[i]->username.c_str(), username)) {
			if (!strcmp(administrators[i]->password.c_str(), password)) {
				IndexOfloggedInAdmin = i;
				return true;
			}
		}
	}
	return false;
}

bool SuperHeroesGame::LogInAsPlayer(const char* username, const char* password) const{
	if (!username || !password)
		throw std::invalid_argument("The username or password doesn't exist");

	for (int i = 0; i < players.GetCount(); i++) {
		if (!strcmp(players[i]->username.c_str(), username)) {
			if (!strcmp(players[i]->password.c_str(), password)) {
				IndexOfloggedInPlayer = i;
				return true;
			}
		}
	}
	return false;
}

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

bool SuperHeroesGame::DeleteOwnProfile() {
	if (IndexOfloggedInPlayer != -1) {
		players.RemoveElement(IndexOfloggedInPlayer);
		IndexOfloggedInPlayer = -1;
		return true;
	}
	return false;
}

bool SuperHeroesGame::IsAdministratorLogged() const{
	return IndexOfloggedInAdmin != -1;
}

bool SuperHeroesGame::IsPlayerLogged() const{
	return IndexOfloggedInPlayer != -1;
}
