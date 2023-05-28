#include "Player.h"

Player::Player(const char* firstName, const char* lastName, const char* email, const char* username, const char* password) : User(firstName, lastName, email, username, password) {}

const char* Player::GetUsername() const{
	return username.c_str();
}
