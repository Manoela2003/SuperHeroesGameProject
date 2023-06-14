#pragma once
#include "String.h"

enum class HeroPower {
	Fire,
	Water,
	Earth
};

enum class HeroPosition {
	Attack,
	Defense
};

class SuperHero {
private:
	String firstName;
	String lastName;
	String nickname;
	HeroPower power;
	unsigned strength;
	double price;
	HeroPosition position;

public:
	SuperHero() = default;
	SuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price);
	SuperHero(SuperHero&& obj);
	SuperHero(const SuperHero& other);

	const char* GetNickname() const;
	double GetPrice() const;
	unsigned GetStrength() const;
	HeroPosition GetPosition() const;

	void SetFirstName(const char* name);
	void SetLastName(const char* name);
	void SetNickname(const char* name);
	void SetHeroPower(const char* power);
	void SetStrength(int strength);
	void SetPrice(double price);
	void SetHeroPosition(HeroPosition position);

	void PrintPower() const;
	void PrintDetailedInfo() const;
	void PrintUndetailedInfo() const;

	int IsDominating(const SuperHero& other) const;
	int IsStrongerThan(const SuperHero& other) const;
}; 

