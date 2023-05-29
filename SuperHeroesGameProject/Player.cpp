#include "Player.h"

Player::Player(const char* firstName, const char* lastName, const char* username, const char* password) : User(firstName, lastName, username, password) {}

Player::Player(const char* firstName, const char* lastName, const char* email, const char* username, const char* password) : User(firstName, lastName, email, username, password) {}

void Player::PrintInfo() const {
	std::cout << "Name: " << firstName << ' ' << lastName << std::endl;
	std::cout << "Email: ";
	if (IsEmailEmpty())
		std::cout << "'email not set'" << std::endl;
	else
		std::cout << email << std::endl;
	std::cout << "Username: " << username << std::endl;
}
