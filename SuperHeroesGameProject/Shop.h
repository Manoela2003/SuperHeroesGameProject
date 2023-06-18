#pragma once
#include "SuperHero.h"
#include "Vector.hpp"
#include "SharedPtr.hpp"

class Shop {
private:
	Vector<SharedPtr<SuperHero>> superHeroes;
	Vector<SharedPtr<SuperHero>> oldHeroes;

public:

	int GetCountOfOldHeroes() const;
	int GetCount() const;
	bool IsShopEmpty() const;
	void AddNewSuperHero(SuperHero&& other);
	void AddNewSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price);
	void AddOldSuperHero(const SuperHero& other);
	bool PrintSuperHeroes() const;
	bool PrintOldSuperHeroes() const;
	void RemoveSuperHero(const SuperHero& hero);
	SuperHero FindSuperHero(const char* nickname) const;
	SuperHero& GetOldSuperHero(int index);
	void RemoveOldSuperHero(int index);
	int IndexOfSuperHero(const char* nickname) const;

	void ReadFromFile(std::ifstream& file);
	void SaveToFile(std::ofstream& file) const;
};

