#pragma once
#include "Vector.hpp"
#include "Administrator.h"
#include "Player.h"
#include "SharedPtr.hpp"

class SuperHeroesGame {
private:
	Vector<SharedPtr<Administrator>> administrators;
	Vector<SharedPtr<Player>> players;

public:
	SuperHeroesGame() = default;

	void AddAdministrator(const Administrator& other);
	void AddPlayer(const Player& other);
};

