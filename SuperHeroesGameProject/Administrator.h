#pragma once
#include "User.h"

class Administrator : private User {
public:
	Administrator(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);
};

