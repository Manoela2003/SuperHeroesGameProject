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
	Player() = default;
	Player(const char* firstName, const char* lastName, const char* username, const char* password);
	Player(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);

	int GetHeroesCount() const;

	void PrintBalance() const;
	void PrintHeroes() const;
	bool BuySuperHero(SuperHero& hero);
	int IndexOfSuperHero(const char* nickname) const;
	void LoseMoney(unsigned amount);
	void EarnMoney(unsigned amount);
	SharedPtr<SuperHero> GetSuperHero(int index) const;

	void RemoveSuperHero(const SuperHero& other);

	void PrintInfo() const override;
	friend class SuperHeroesGame;
};

