#include "User.h"
#include "HelperFunctions.h"

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
	if (!username)
		throw std::invalid_argument("The username doesn't exist");

	this->username = username;
}

void User::SetPassword(const char* password) {
	IsPasswordValid(password);

	this->password = password;
}
