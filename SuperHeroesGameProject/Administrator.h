#pragma once
#include "User.h"

class Administrator : public User {
public:
	Administrator() = default;
	Administrator(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);

	friend class SuperHeroesGame;

};

