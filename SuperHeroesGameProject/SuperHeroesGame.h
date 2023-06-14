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

	mutable int indexOfloggedInAdmin = -1;
	mutable int indexOfloggedInPlayer = -1;

public:
	SuperHeroesGame() = default;

	bool LogInAsAdministrator(const char* username, const char* password) const;
	bool LogInAsPlayer(const char* username, const char* password) const;
	bool AddAdministrator(const char* firstName, const char* lastName, const char* username, const char* password);
	bool AddPlayer(const char* firstName, const char* lastName, const char* username, const char* password);
	bool DeletePlayer(const char* username);
	bool DeleteOwnProfile();
	bool AddSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price);
	
	void PrintAllPlayers() const;
	bool PrintSpecificPlayer(const char* username) const;
	void PrintAllAdmins() const;
	bool PrintSpecificAdministrator(const char* firstName) const;
	bool IsAdministratorLogged() const;
	bool IsPlayerLogged() const;
	void PrintOtherPlayersInfo() const;
	bool PrintShop() const;
	void PrintPlayerBalance() const;

	bool BuySuperHero(const char* nickname);
	int IndexOfPlayer(const char* username) const;
	int IndexOfSuperHero(const char* nickname, int playerIndex = -1) const;
	bool Attack(int playerIndex, int attackerIndex, int attackedIndex);

	int GetCountOfSuperHeroes(int playerIndex) const;
	bool ChangePositionOfSuperHero(const char* nickname);

	void LogOut() const;
};

