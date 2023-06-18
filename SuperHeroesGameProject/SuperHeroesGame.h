#pragma once
#include "Administrator.h"
#include "Player.h"
#include "Shop.h"
#include "UniquePtr.hpp"

class SuperHeroesGame {
private:
	Vector<SharedPtr<Administrator>> administrators;
	Vector<SharedPtr<Player>> players;
	UniquePtr<Shop> shop = new Shop();

	Vector<bool> loggedIn;

	mutable int moves = 0;
	mutable int indexOfloggedInAdmin = -1;
	mutable int indexOfloggedInPlayer = -1;

	void SaveAdminsToFile() const;
	void SavePlayersToFile() const;
	void SaveShopToFile() const;
	void SaveLoggedInToFile() const;

	void ReadAdminsFromFile();
	void ReadPlayersFromFile();
	void ReadShopFromFile();
	void ReadLoggedInFromFile();

	void OrderPlayers(Vector<SharedPtr<Player>>& players);

public:
	SuperHeroesGame();

	bool LogInAsAdministrator(const char* username, const char* password) const;
	bool LogInAsPlayer(const char* username, const char* password);
	bool AddAdministrator(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);
	bool AddPlayer(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);
	bool DeletePlayer(const char* username);
	bool DeleteOwnProfile();
	bool AddSuperHero(SuperHero&& other);
	bool AddSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price);
	SuperHero& GetOldSuperHero(int index);

	void PrintAllPlayers() const;
	bool PrintSpecificPlayer(const char* username) const;
	void PrintAllAdmins() const;
	bool PrintSpecificAdministrator(const char* firstName) const;
	bool IsAdministratorLogged() const;
	bool IsPlayerLogged() const;
	void PrintOtherPlayersInfo() const;
	bool PrintShop() const;
	bool PrintOldSuperHeroes() const;
	void PrintPlayerBalance() const;
	void PrintPlayerSuperHeroes() const;

	void ShowRanking() const;
	void SaveRanking();
	bool BuySuperHero(const char* nickname);
	int IndexOfPlayer(const char* username) const;
	int IndexOfSuperHero(const char* nickname, int playerIndex = -1) const;
	void AttackDefenseless(int playerIndex, int attackerIndex);
	bool Attack(int playerIndex, int attackerIndex, int attackedIndex);

	int GetCountOfOldHeroes() const;
	int GetCountOfSuperHeroes(int playerIndex) const;
	bool ChangePositionOfSuperHero(const char* nickname);
	bool AreThereAdministrators() const;
	int GetHeroesInShopCount() const;
	void RemoveOldSuperHero(int index);

	bool CheckMoves();
	void ManageLoggedIn(int index);
	void GivePeriodicalMoney();
	void RestartPeriod();

	void LogOut() const;

	~SuperHeroesGame();
};

