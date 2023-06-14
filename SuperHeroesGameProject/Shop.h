#pragma once
#include "SuperHero.h"
#include "Vector.hpp"
#include "SharedPtr.hpp"

class Shop {
private:
	Vector<SharedPtr<SuperHero>> superHeroes;

public:
	bool IsShopEmpty() const;
	void AddNewSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price);
	bool PrintSuperHeroes() const;
	void RemoveSuperHero(const SuperHero& hero);
	SuperHero FindSuperHero(const char* nickname) const;

	void ReadFromFile(const char* fileName);
	void SaveToFile(const char* fileName) const;
};

