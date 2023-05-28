#pragma once
#include "Vector.hpp"
#include "Administrator.h"
#include "Player.h"
#include "SharedPtr.hpp"

class SuperHeroesGame {
private:
	Vector<SharedPtr<Administrator>> administrators;
	Vector<SharedPtr<Player>> players;

	unsigned IndexOfloggedInAdmin = -1;

public:
	SuperHeroesGame() = default;

	bool AddAdministrator(const Administrator& other);
	bool AddPlayer(const Player& other);
	bool DeletePlayer(const char* username);

};

