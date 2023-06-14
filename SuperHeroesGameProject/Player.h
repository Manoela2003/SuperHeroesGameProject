#pragma once
#include "GlobalConstants.h"
#include "User.h"
#include "Vector.hpp"
#include "SuperHero.h"
#include "SharedPtr.hpp"

class Player : public User {
private:
	double balance = player_Starting_Balance;
	Vector<SharedPtr<SuperHero>> heroes;

public:
	Player(const char* firstName, const char* lastName, const char* username, const char* password);
	Player(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);

	void PrintBalance() const;
	void PrintHeroes() const;
	bool BuySuperHero(SuperHero& hero);

	void PrintInfo() const override;
	friend class SuperHeroesGame;
};

