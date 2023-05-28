#pragma once
#include "Administrator.h"
#include "Player.h"

class SuperHeroesGame {
private:
	Vector<SharedPtr<Administrator>> administrators;
	Vector<SharedPtr<Player>> players;

	mutable unsigned IndexOfloggedInAdmin = -1;
	mutable unsigned IndexOfloggedInPlayer = -1;

public:
	SuperHeroesGame() = default;

	bool LogInAsAdministrator(const char* username, const char* password) const;
	bool LogInAsPlayer(const char* username, const char* password) const;
	bool AddAdministrator(const Administrator& other);
	bool AddPlayer(const Player& other);
	bool DeletePlayer(const char* username);
	bool DeleteOwnProfile();

	bool IsAdministratorLogged() const;
	bool IsPlayerLogged() const;
};

