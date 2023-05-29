#pragma once
#include "User.h"

class Administrator : public User {
public:
	Administrator(const char* firstName, const char* lastName, const char* username, const char* password);
	Administrator() = default;
	Administrator(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);

	void PrintInfo() const override;

	friend class SuperHeroesGame;
};

