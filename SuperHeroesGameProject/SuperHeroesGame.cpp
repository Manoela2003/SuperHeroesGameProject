#include "SuperHeroesGame.h"
#include <cmath>

bool SuperHeroesGame::LogInAsAdministrator(const char* username, const char* password) const {
	if (!username || !password)
		throw std::invalid_argument("The username or password doesn't exist");

	for (int i = 0; i < administrators.GetCount(); i++) {
		if (!strcmp(administrators[i]->username.c_str(), username)) {
			if (!strcmp(administrators[i]->password.c_str(), password)) {
				indexOfloggedInAdmin = i;
				return true;
			}
		}
	}
	return false;
}

bool SuperHeroesGame::LogInAsPlayer(const char* username, const char* password) const {
	if (!username || !password)
		throw std::invalid_argument("The username or password doesn't exist");

	for (int i = 0; i < players.GetCount(); i++) {
		if (!strcmp(players[i]->username.c_str(), username)) {
			if (!strcmp(players[i]->password.c_str(), password)) {
				indexOfloggedInPlayer = i;
				return true;
			}
		}
	}
	return false;
}

bool SuperHeroesGame::AddAdministrator(const char* firstName, const char* lastName, const char* username, const char* password) {
	if (indexOfloggedInAdmin != -1) {
		administrators.AddElement(new Administrator(firstName, lastName, username, password));
		return true;
	}
	return false;
}

bool SuperHeroesGame::AddPlayer(const char* firstName, const char* lastName, const char* username, const char* password) {
	if (indexOfloggedInAdmin != -1) {
		players.AddElement(new Player(firstName, lastName, username, password));
		return true;
	}
	return false;
}

bool SuperHeroesGame::DeletePlayer(const char* username) {
	if (!username)
		throw std::invalid_argument("The username doesn't exist");

	if (indexOfloggedInAdmin == -1)
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
	if (indexOfloggedInPlayer != -1) {
		players.RemoveElement(indexOfloggedInPlayer);
		indexOfloggedInPlayer = -1;
		return true;
	}
	return false;
}

bool SuperHeroesGame::AddSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price) {
	if (indexOfloggedInAdmin != -1) {
		shop->AddNewSuperHero(firstName, lastName, nickname, power, strength, price);
		return true;
	}
	return false;
}

void SuperHeroesGame::PrintAllPlayers() const {
	if (indexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can have such information!");

	for (int i = 0; i < players.GetCount(); i++) {
		players[i]->PrintInfo();
	}
}

bool SuperHeroesGame::PrintSpecificPlayer(const char* username) const {
	if (indexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can have such information!");

	for (int i = 0; i < players.GetCount(); i++) {
		if (!strcmp(players[i]->username.c_str(), username)) {
			players[i]->PrintInfo();
			return true;
		}
	}
	return false;
}

void SuperHeroesGame::PrintAllAdmins() const {
	if (indexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can have such information!");

	for (int i = 0; i < administrators.GetCount(); i++) {
		administrators[i]->PrintInfo();
	}
}

bool SuperHeroesGame::PrintSpecificAdministrator(const char* firstName) const {
	if (indexOfloggedInAdmin == -1)
		throw std::logic_error("Only administrators can have such information!");

	for (int i = 0; i < administrators.GetCount(); i++) {
		if (!strcmp(administrators[i]->firstName.c_str(), firstName)) {
			administrators[i]->PrintInfo();
			return true;
		}
	}
	return false;
}

bool SuperHeroesGame::IsAdministratorLogged() const {
	return indexOfloggedInAdmin != -1;
}

bool SuperHeroesGame::IsPlayerLogged() const {
	return indexOfloggedInPlayer != -1;
}

void SuperHeroesGame::PrintOtherPlayersInfo() const {
	for (int i = 0; i < players.GetCount(); i++) {
		if (i == indexOfloggedInPlayer)
			continue;
		std::cout << i + 1 << ". ";
		players[i]->PrintUsername();
		players[i]->PrintBalance();
		players[i]->PrintHeroes();
	}
}

bool SuperHeroesGame::PrintShop() const {
	return shop->PrintSuperHeroes();
}

void SuperHeroesGame::PrintPlayerBalance() const {
	if (indexOfloggedInPlayer != -1)
		players[indexOfloggedInPlayer]->PrintBalance();
	else
		throw std::logic_error("You must be logged in first");
}

bool SuperHeroesGame::BuySuperHero(const char* nickname) {
	if (indexOfloggedInPlayer != -1) {
		SuperHero temp = shop->FindSuperHero(nickname);
		if (players[indexOfloggedInPlayer]->BuySuperHero(temp)) {
			shop->RemoveSuperHero(temp);
			return true;
		}
		return false;
	}

	throw std::logic_error("You must be logged in to buy superHero");
}

int SuperHeroesGame::IndexOfPlayer(const char* username) const {
	if (username == nullptr)
		throw std::invalid_argument("The nickname doesn't exist");

	for (int i = 0; i < players.GetCount(); i++) {
		if (!strcmp(players[i]->username.c_str(), username))
			return i;
	}
	return -1;
}

int SuperHeroesGame::IndexOfSuperHero(const char* nickname, int playerIndex) const {
	if (playerIndex == -1)
		playerIndex = indexOfloggedInPlayer;

	return players[playerIndex]->IndexOfSuperHero(nickname);
}

bool SuperHeroesGame::Attack(int playerIndex, int attackerIndex, int attackedIndex) {
	SharedPtr<SuperHero> attacker = players[indexOfloggedInPlayer]->GetSuperHero(attackerIndex);
	SharedPtr<SuperHero> attacked = players[playerIndex]->GetSuperHero(attackedIndex);
	int value = attacker->IsDominating(*attacked);
	if (value == 1) {
		attacker->SetStrength(2 * attacker->GetStrength());
	}
	else {
		attacked->SetStrength(2 * attacked->GetStrength());
	}

	value = attacker->IsStrongerThan(*attacked);
	switch (value) {
		int difference = attacker->GetStrength() - attacked->GetStrength();
	case 1:
		if (attacked->GetPosition() == HeroPosition::Attack)
			players[playerIndex]->LoseMoney(difference);

		players[indexOfloggedInPlayer]->EarnMoney(difference);
		players[playerIndex]->RemoveSuperHero(*attacked);
		return true;
		break;
	case -1:
		players[playerIndex]->EarnMoney(win_Defense_Money);
		players[indexOfloggedInPlayer]->LoseMoney(abs(difference) * 2);
		players[indexOfloggedInPlayer]->RemoveSuperHero(*attacker);
		return false;
		break;
	case 0:
		players[indexOfloggedInPlayer]->LoseMoney(lose_Attack_Money);
		return false;
		break;
	}
}

int SuperHeroesGame::GetCountOfSuperHeroes(int playerIndex) const{
	return players[playerIndex]->GetHeroesCount();
}

void SuperHeroesGame::LogOut() const {
	if (indexOfloggedInAdmin == -1 && indexOfloggedInPlayer == -1)
		throw std::logic_error("You are not logged in");

	indexOfloggedInAdmin = indexOfloggedInPlayer = -1;
}
