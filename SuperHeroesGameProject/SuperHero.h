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

	void SetFirstName(const char* name);
	void SetLastName(const char* name);
	void SetNickname(const char* name);
	void SetHeroPower(const char* power);
	void SetStrength(int strength);
	void SetPrice(double price);
	void SetHeroPosition(HeroPosition position);

	void PrintPower() const;
	void PrintSuperHero() const;
};

