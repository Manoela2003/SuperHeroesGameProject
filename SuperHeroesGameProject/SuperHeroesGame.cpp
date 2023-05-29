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

bool SuperHeroesGame::AddAdministrator(const char* firstName, const char* lastName, const char* username, const char* password) {
	if (IndexOfloggedInAdmin != -1) {
		administrators.AddElement(new Administrator(firstName, lastName, username, password));
		return true;
	}
	return false;
}

bool SuperHeroesGame::AddPlayer(const char* firstName, const char* lastName, const char* username, const char* password) {
	if (IndexOfloggedInAdmin != -1) {
		players.AddElement(new Player(firstName, lastName, username, password));
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
		if (!strcmp(players[i]->username.c_str(), username)) {
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

void SuperHeroesGame::PrintAllPlayers() const{
	if (IndexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can have such information!");

	for (int i = 0; i < players.GetCount(); i++) {
		players[i]->PrintInfo();
	}
}

bool SuperHeroesGame::PrintSpecificPlayer(const char* username) const{
	if (IndexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can have such information!");

	for (int i = 0; i < players.GetCount(); i++) {
		if (!strcmp(players[i]->username.c_str(), username)) {
			players[i]->PrintInfo();
			return true;
		}
	}
	return false;
}

void SuperHeroesGame::PrintAllAdmins() const{
	if(IndexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can have such information!");

	for (int i = 0; i < administrators.GetCount(); i++) {
		administrators[i]->PrintInfo();
	}
}

bool SuperHeroesGame::PrintSpecificAdministrator(const char* firstName) const{
	if (IndexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can have such information!");

	for (int i = 0; i < administrators.GetCount(); i++) {
		if (!strcmp(administrators[i]->firstName.c_str(), firstName)) {
			administrators[i]->PrintInfo();
			return true;
		}
	}
	return false;
}

bool SuperHeroesGame::IsAdministratorLogged() const{
	return IndexOfloggedInAdmin != -1;
}

bool SuperHeroesGame::IsPlayerLogged() const{
	return IndexOfloggedInPlayer != -1;
}
