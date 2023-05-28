#pragma once
#include "GlobalConstants.h"
#include "User.h"
#include "Vector.hpp"
#include "SuperHero.h"
#include "SharedPtr.hpp"

class Player : public User {
private:
	double balance = player_Starting_Balance;
	Vector<SharedPtr<SuperHero>> deck;

public:
	Player(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);

	friend class SuperHeroesGame;

};

