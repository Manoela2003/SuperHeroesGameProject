#pragma once
#include "User.h"
#include "Vector.hpp"
#include "GlobalConstants.h"

class Player : private User {
private:
	double balance = player_Starting_Balance;

public:
	Player(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);
};

