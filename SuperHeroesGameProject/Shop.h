#pragma once
#include "SuperHero.h"
#include "Vector.hpp"
#include "SharedPtr.hpp"

class Shop {
private:
	Vector<SharedPtr<SuperHero>> superHeroes;

public:
	int GetCount() const;
	bool IsShopEmpty() const;
	void AddNewSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price);
	bool PrintSuperHeroes() const;
	void RemoveSuperHero(const SuperHero& hero);
	SuperHero FindSuperHero(const char* nickname) const;

	void ReadFromFile(std::ifstream& file);
	void SaveToFile(std::ofstream& file) const;
};

