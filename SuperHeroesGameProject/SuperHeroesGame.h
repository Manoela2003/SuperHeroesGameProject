#pragma once
#include "Administrator.h"
#include "Player.h"
#include "Shop.h"
#include "UniquePtr.hpp"

class SuperHeroesGame {
private:
	Vector<SharedPtr<Administrator>> administrators;
	Vector<SharedPtr<Player>> players;
	UniquePtr<Shop> shop;

	mutable unsigned IndexOfloggedInAdmin = -1;
	mutable unsigned IndexOfloggedInPlayer = -1;

public:
	SuperHeroesGame() = default;

	bool LogInAsAdministrator(const char* username, const char* password) const;
	bool LogInAsPlayer(const char* username, const char* password) const;
	bool AddAdministrator(const char* firstName, const char* lastName, const char* username, const char* password);
	bool AddPlayer(const char* firstName, const char* lastName, const char* username, const char* password);
	bool DeletePlayer(const char* username);
	bool DeleteOwnProfile();
	
	void PrintAllPlayers() const;
	bool PrintSpecificPlayer(const char* username) const;

	void PrintAllAdmins() const;
	bool PrintSpecificAdministrator(const char* firstName) const;

	bool IsAdministratorLogged() const;
	bool IsPlayerLogged() const;
};

