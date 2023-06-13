#include "User.h"
#include "HelperFunctions.h"

User::User(const char* firstName, const char* lastName, const char* username, const char* password) {
	SetFirstName(firstName);
	SetLastName(lastName);
	SetUsername(username);
	SetPassword(password);
}

User::User(const char* firstName, const char* lastName, const char* email, const char* username, const char* password) {
	SetFirstName(firstName);
	SetLastName(lastName);
	SetEmail(email);
	SetUsername(username);
	SetPassword(password);
}

void User::SetFirstName(const char* name) {
	IsNameValid(name);

	firstName = name;
}

void User::SetLastName(const char* name) {
	IsNameValid(name);

	lastName = name;
}

void User::SetEmail(const char* email) {
	IsEmailValid(email);

	this->email = email;
}

void User::SetUsername(const char* username) {
	IsUsernameValid(username);

	this->username = username;
}

void User::SetPassword(const char* password) {
	IsPasswordValid(password);

	this->password = password;
}

void User::PrintName() const {
	std::cout << "Name: " << firstName << ' ' << lastName << std::endl;
}

void User::PrintEmail() const {
	std::cout << "Email: ";
	if (IsEmailEmpty())
		std::cout << "'email not set'" << std::endl;
	else
		std::cout << email << std::endl;
}

void User::PrintUsername() const{
	std::cout << "Username: " << username << std::endl;
}

bool User::IsEmailEmpty() const {
	return email[0] == '\0';
}
