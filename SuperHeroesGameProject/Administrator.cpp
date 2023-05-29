#include "Administrator.h"

Administrator::Administrator(const char* firstName, const char* lastName, const char* username, const char* password) : User(firstName, lastName, username, password) {}

Administrator::Administrator(const char* firstName, const char* lastName, const char* email, const char* username, const char* password) : User(firstName, lastName, email, username, password) {}

void Administrator::PrintInfo() const {
	std::cout << "Name: " << firstName << lastName << std::endl;
	std::cout << "Email: ";
	if (IsEmailEmpty())
		std::cout << "'email not set'" << std::endl;
	else
		std::cout << email << std::endl;
}
