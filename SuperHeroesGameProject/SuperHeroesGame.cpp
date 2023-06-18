#include "SuperHeroesGame.h"
#include <cmath>
#include "FileFunctions.h"

SuperHeroesGame::SuperHeroesGame() {
	ReadAdminsFromFile();
	ReadPlayersFromFile();
	ReadShopFromFile();
}

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

bool SuperHeroesGame::AddAdministrator(const char* firstName, const char* lastName, const char* email, const char* username, const char* password) {
	if (indexOfloggedInAdmin != -1) {
		administrators.AddElement(new Administrator(firstName, lastName, email, username, password));
		return true;
	}
	return false;
}

bool SuperHeroesGame::AddPlayer(const char* firstName, const char* lastName, const char* email, const char* username, const char* password) {
	if (indexOfloggedInAdmin != -1) {
		players.AddElement(new Player(firstName, lastName, email, username, password));
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

	for (int i = 0; i < players.GetCount(); i++)
		players[i]->PrintInfo();
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

	for (int i = 0; i < administrators.GetCount(); i++)
		administrators[i]->PrintInfo();
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
	int difference = attacker->GetStrength() - attacked->GetStrength();
	switch (value) {
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

int SuperHeroesGame::GetCountOfSuperHeroes(int playerIndex) const {
	return players[playerIndex]->GetHeroesCount();
}

bool SuperHeroesGame::ChangePositionOfSuperHero(const char* nickname) {
	int index = IndexOfSuperHero(nickname);

	if (index == -1)
		return false;

	players[indexOfloggedInPlayer]->GetSuperHero(index)->ChangePosition();
	return true;
}

bool SuperHeroesGame::AreThereAdministrators() const {
	if (administrators.GetCount() == 0) {
		indexOfloggedInAdmin = 0; // gives administrator permissions
		return false;
	}
	return true;
}

void SuperHeroesGame::LogOut() const {
	if (indexOfloggedInAdmin == -1 && indexOfloggedInPlayer == -1)
		throw std::logic_error("You are not logged in");

	indexOfloggedInAdmin = indexOfloggedInPlayer = -1;
}

void SuperHeroesGame::SaveAdminsToFile() const {
	std::ofstream file(adminFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = administrators.GetCount();
	if (count == 0) // leaves the file empty
		return;

	file.write((const char*)&count, sizeof(count));
	for (int i = 0; i < count; i++) {
		administrators[i]->firstName.SaveToFile(file);
		administrators[i]->lastName.SaveToFile(file);
		administrators[i]->email.SaveToFile(file);
		administrators[i]->username.SaveToFile(file);
		administrators[i]->password.SaveToFile(file);
	}

	file.close();
}

void SuperHeroesGame::SavePlayersToFile() const {
	std::ofstream file(playerFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = players.GetCount();
	if (count == 0) // leaves the file empty
		return;

	file.write((const char*)&count, sizeof(count));
	for (int i = 0; i < count; i++) {
		players[i]->firstName.SaveToFile(file);
		players[i]->lastName.SaveToFile(file);
		players[i]->email.SaveToFile(file);
		players[i]->username.SaveToFile(file);
		players[i]->password.SaveToFile(file);
		file.write((const char*)&players[i]->balance, sizeof(players[i]->balance));
		unsigned heroesCount = players[i]->heroes.GetCount();
		file.write((const char*)&heroesCount, sizeof(heroesCount));
		for (int i = 0; i < heroesCount; i++)
			players[i]->heroes[i]->SaveToFile(file);
	}

	file.close();
}

void SuperHeroesGame::SaveShopToFile() const {
	std::ofstream file(shopFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = shop->GetCount();
	if (count == 0) // leaves the file empty
		return;

	file.write((const char*)&count, sizeof(count));
	shop->SaveToFile(file);

	file.close();
}

static void ReadUser(std::ifstream& file, char* fName, char* lName, char* email, char* username, char* password) {
	size_t size;
	file.read((char*)&size, sizeof(size));
	file.read((char*)fName, size + 1);
	file.read((char*)&size, sizeof(size));
	file.read((char*)lName, size + 1);
	file.read((char*)&size, sizeof(size));
	file.read((char*)email, size + 1);
	file.read((char*)&size, sizeof(size));
	file.read((char*)username, size + 1);
	file.read((char*)&size, sizeof(size));
	file.read((char*)password, size + 1);
}

void SuperHeroesGame::ReadAdminsFromFile(){
	std::ifstream file(adminFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = 0;
	file.read((char*)&count, sizeof(count));

	for (int i = 0; i < count; i++) {
		char fName[buffer_Max_Size];
		char lName[buffer_Max_Size];
		char email[buffer_Max_Size];
		char username[buffer_Max_Size];
		char password[buffer_Max_Size];
		ReadUser(file, fName, lName, email, username, password);
		administrators.AddElement(new Administrator(fName, lName, email, username, password));
	}

	file.close();
}

void SuperHeroesGame::ReadPlayersFromFile(){
	std::ifstream file(playerFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = 0;
	file.read((char*)&count, sizeof(count));

	for (int i = 0; i < count; i++) {
		char fName[buffer_Max_Size];
		char lName[buffer_Max_Size];
		char email[buffer_Max_Size];
		char username[buffer_Max_Size];
		char password[buffer_Max_Size];
		ReadUser(file, fName, lName, email, username, password);
		players.AddElement(new Player(fName, lName, email, username, password));
		file.read((char*)&players[i]->balance, sizeof(players[i]->balance));
		unsigned heroesCount;
		file.read((char*)&heroesCount, sizeof(heroesCount));
		for (int j = 0; j < heroesCount; j++) {
			SuperHero hero;
			hero.ReadFromFile(file);
			players[j]->heroes.AddElement(new SuperHero(std::move(hero)));
		}
	}

	file.close();
}

void SuperHeroesGame::ReadShopFromFile(){
	std::ifstream file(shopFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	shop->ReadFromFile(file);

	file.close();
}

SuperHeroesGame::~SuperHeroesGame() {
	SaveAdminsToFile();
	SavePlayersToFile();
	SaveShopToFile();
}
