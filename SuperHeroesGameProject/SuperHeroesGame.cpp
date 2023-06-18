#include "SuperHeroesGame.h"
#include <cmath>

SuperHeroesGame::SuperHeroesGame() {
	ReadAdminsFromFile();
	ReadPlayersFromFile();
	ReadShopFromFile();
	ReadLoggedInFromFile();
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

bool SuperHeroesGame::LogInAsPlayer(const char* username, const char* password) {
	if (!username || !password)
		throw std::invalid_argument("The username or password doesn't exist");

	for (int i = 0; i < players.GetCount(); i++) {
		if (!strcmp(players[i]->username.c_str(), username)) {
			if (!strcmp(players[i]->password.c_str(), password)) {
				indexOfloggedInPlayer = i;
				ManageLoggedIn(i);
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
		loggedIn.AddElement(false);
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

bool SuperHeroesGame::AddSuperHero(SuperHero&& other) {
	if (indexOfloggedInAdmin != -1) {
		shop->AddNewSuperHero(std::move(other));
		return true;
	}
	return false;
}

bool SuperHeroesGame::AddSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price) {
	if (indexOfloggedInAdmin != -1) {
		for (int i = 0; i < players.GetCount(); i++) {
			if (players[i]->IndexOfSuperHero(nickname) != -1) {
				std::cout << "There cannot be duplicated heroes!" << std::endl;
				return true;
			}
		}

		if (shop->IndexOfSuperHero(nickname) != -1) {
			std::cout << "There cannot be duplicated heroes!" << std::endl;
			return true;
		}

		shop->AddNewSuperHero(firstName, lastName, nickname, power, strength, price);
		return true;
	}
	return false;
}

SuperHero& SuperHeroesGame::GetOldSuperHero(int index) {
	return shop->GetOldSuperHero(index);
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
			std::cin.ignore();
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
	if (players.GetCount() == 1) {
		std::cout << "There are no other players!" << std::endl;
		return;
	}

	int increment = 1;

	for (int i = 0; i < players.GetCount(); i++) {
		if (i == indexOfloggedInPlayer) {
			increment = 0;
			continue;
		}
		std::cout << i + increment << ". ";
		players[i]->PrintUsername();
		players[i]->PrintBalance();
		players[i]->PrintHeroes();
	}
}

bool SuperHeroesGame::PrintShop() const {
	return shop->PrintSuperHeroes();
}

bool SuperHeroesGame::PrintOldSuperHeroes() const {
	return shop->PrintOldSuperHeroes();
}

void SuperHeroesGame::PrintPlayerBalance() const {
	if (indexOfloggedInPlayer != -1)
		players[indexOfloggedInPlayer]->PrintBalance();
	else
		throw std::logic_error("You must be logged in first");
}

void SuperHeroesGame::PrintPlayerSuperHeroes() const {
	if (indexOfloggedInPlayer == -1)
		throw std::logic_error("Only players can see their Superheroes");

	int count = players[indexOfloggedInPlayer]->GetHeroesCount();
	if (count == 0) {
		std::cout << "You don't have any SuperHeroes!" << std::endl;
		return;
	}

	for (int i = 0; i < count; i++)
		players[indexOfloggedInPlayer]->heroes[i]->PrintAllInfo();
}

void SuperHeroesGame::ShowRanking() const {
	std::ifstream file(rankingFile);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	for (int i = 0; i < players.GetCount(); i++) {
		char buff[buffer_Max_Size];
		file.getline(buff, buffer_Max_Size);
		file.ignore();
		std::cout << buff;
	}
}

void SuperHeroesGame::SaveRanking() {
	std::ofstream file(rankingFile);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	Vector<SharedPtr<Player>> orderedPlayers;

	OrderPlayers(orderedPlayers);

	for (int i = 0; i < orderedPlayers.GetCount(); i++) {
		file << (i + 1) << ". ";
		orderedPlayers[i]->SaveToFile(file);
	}

	file.close();
}

bool SuperHeroesGame::BuySuperHero(const char* nickname) {
	if (indexOfloggedInPlayer != -1) {
		SuperHero hero = shop->FindSuperHero(nickname);
		if (players[indexOfloggedInPlayer]->BuySuperHero(hero)) {
			shop->RemoveSuperHero(hero);
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

void SuperHeroesGame::AttackDefenseless(int playerIndex, int attackerIndex) {
	SharedPtr<SuperHero> attacker = players[indexOfloggedInPlayer]->GetSuperHero(attackerIndex);
	players[playerIndex]->LoseMoney(attacker->GetStrength());
	players[indexOfloggedInPlayer]->EarnMoney(win_NoHeroes_Money);
}

bool SuperHeroesGame::Attack(int playerIndex, int attackerIndex, int attackedIndex) {
	if (CheckMoves()) {
		SharedPtr<SuperHero> attacker = players[indexOfloggedInPlayer]->GetSuperHero(attackerIndex);
		SharedPtr<SuperHero> attacked = players[playerIndex]->GetSuperHero(attackedIndex);
		int value = attacker->IsDominating(*attacked);

		int attackerIncrement = 1, attackedIncrement = 1;
		if (value == 1)
			attackerIncrement = 2;
		else if (value == -1)
			attackedIncrement = 2;

		value = attacker->IsStrongerThan(*attacked, attackerIncrement, attackedIncrement);
		int difference = attacker->GetStrength() * attackerIncrement
			- attacked->GetStrength() * attackedIncrement;

		switch (value) {
		case 1:
			if (attacked->GetPosition() == HeroPosition::Attack)
				players[playerIndex]->LoseMoney(difference);

			players[indexOfloggedInPlayer]->EarnMoney(difference);
			shop->AddOldSuperHero(*attacked);
			players[playerIndex]->RemoveSuperHero(*attacked);
			return true;
			break;
		case -1:
			players[playerIndex]->EarnMoney(win_Defense_Money);
			players[indexOfloggedInPlayer]->LoseMoney(abs(difference) * 2);
			shop->AddOldSuperHero(*attacker);
			players[indexOfloggedInPlayer]->RemoveSuperHero(*attacker);
			return false;
			break;
		case 0:
			players[indexOfloggedInPlayer]->LoseMoney(lose_Attack_Money);
			return false;
			break;
		}
	}
}

int SuperHeroesGame::GetCountOfOldHeroes() const {
	return shop->GetCountOfOldHeroes();
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

int SuperHeroesGame::GetHeroesInShopCount() const {
	return shop->GetCount();
}

void SuperHeroesGame::RemoveOldSuperHero(int index) {
	shop->RemoveOldSuperHero(index);
}

bool SuperHeroesGame::CheckMoves() {
	if (moves == 3) {
		std::cout << "You have reached the max moves for your turn!" << std::endl;
		return false;
	}
	else {
		moves++;
		return true;
	}
}

void SuperHeroesGame::ManageLoggedIn(int index) {
	if (loggedIn[index] == true) {
		RestartPeriod();
		GivePeriodicalMoney();
	}
	else
		loggedIn[index] = true;
}

void SuperHeroesGame::GivePeriodicalMoney() {
	for (int i = 0; i < players.GetCount(); i++)
		players[i]->EarnMoney(periodically_Won_Money);
}

void SuperHeroesGame::RestartPeriod() {
	for (int i = 0; i < loggedIn.GetCount(); i++) {
		loggedIn[i] = false;
	}
}

void SuperHeroesGame::LogOut() const {
	if (indexOfloggedInAdmin == -1 && indexOfloggedInPlayer == -1)
		throw std::logic_error("You are not logged in");

	if (indexOfloggedInPlayer != -1)
		moves = 0;

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
		for (int j = 0; j < heroesCount; j++)
			players[i]->heroes[j]->SaveToFile(file);
	}

	file.close();
}

void SuperHeroesGame::SaveShopToFile() const {
	std::ofstream file(shopFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	shop->SaveToFile(file);

	file.close();
}

void SuperHeroesGame::SaveLoggedInToFile() const {
	std::ofstream file(loggedInFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = loggedIn.GetCount();
	file.write((const char*)&count, sizeof(count));
	for (int i = 0; i < count; i++)
		file.write((const char*)&loggedIn[i], sizeof(loggedIn[i]));

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

void SuperHeroesGame::ReadAdminsFromFile() {
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

void SuperHeroesGame::ReadPlayersFromFile() {
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
			players[i]->heroes.AddElement(new SuperHero(std::move(hero)));
		}
	}

	file.close();
}

void SuperHeroesGame::ReadShopFromFile() {
	std::ifstream file(shopFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	shop->ReadFromFile(file);

	file.close();
}

void SuperHeroesGame::ReadLoggedInFromFile() {
	std::ifstream file(loggedInFile, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = 0;
	file.read((char*)&count, sizeof(count));

	for (int i = 0; i < count; i++) {
		bool temp = false;
		file.read((char*)&temp, sizeof(temp));
		loggedIn.AddElement(temp);
	}

	file.close();
}

void SuperHeroesGame::OrderPlayers(Vector<SharedPtr<Player>>& players) {
	for (int i = 0; i < players.GetCount(); i++) {
		int index = i;
		double maxBalance = players[i]->balance;
		for (int j = i + 1; j < players.GetCount(); j++) {
			if (players[j]->balance > maxBalance) {
				maxBalance = players[j]->balance;
				index = j;
			}
		}
		if (i != index)
			players.Swap(players[i], players[index]);
	}
}

SuperHeroesGame::~SuperHeroesGame() {
	SaveAdminsToFile();
	SavePlayersToFile();
	SaveShopToFile();
	SaveLoggedInToFile();
}
