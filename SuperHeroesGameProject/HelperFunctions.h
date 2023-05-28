#pragma once
#include <cstring>
#include <stdexcept>

bool ContainsDigits(const char* name) {
	for (int i = 0; i < strlen(name); i++) {
		if (name[i] >= '0' && name[i] <= '9')
			return true;
	}
	return false;
}

bool ContainsCapitalLetter(const char* name) {
	for (int i = 0; i < strlen(name); i++) {
		if (name[i] >= 'A' && name[i] <= 'Z')
			return true;
	}
	return false;
}

bool ContainsLowerCaseLetter(const char* name) {
	for (int i = 0; i < strlen(name); i++) {
		if (name[i] >= 'a' && name[i] <= 'z')
			return true;
	}
	return false;
}

bool ContainsAsperand(const char* name) {
	for (int i = 0; i < strlen(name); i++) {
		if (name[i] == '@')
			return true;
	}
	return false;
}

bool ContainsSpecialSymbols(const char* name) {
	for (int i = 0; i < strlen(name); i++) {
		if (name[i] == '@' || name[i] == '#' || name[i] == '-' || name[i] == '_')
			return true;
	}
	return false;
}

bool StartsWithCapitalLetter(const char* name) {
	return (name[0] >= 'A' && name[0] <= 'Z') ? true : false;
}

bool IsEmailValid(const char* email) {
	if (!email)
		throw std::invalid_argument("The email doesn't exist");

	if(!ContainsAsperand(email))
		throw std::logic_error("Not a valid email!. It must contains '@'");
}

void IsNameValid(const char* name) {
	if (!name)
		throw std::invalid_argument("The name doesn't exist");

	if (!StartsWithCapitalLetter(name))
		throw std::logic_error("The name must start with capital letter");

	if (ContainsDigits(name))
		throw std::logic_error("The name cannot contain digits");
}

void IsPasswordValid(const char* pass) {
	if (!pass)
		throw std::invalid_argument("The password doesn't exist");

	if (strlen(pass) < 8)
		throw std::logic_error("The password must be at least 8 characters long");

	if (!ContainsDigits(pass))
		throw std::logic_error("The password must contains at least one digit");

	if (!ContainsCapitalLetter(pass))
		throw std::logic_error("The password must contains at least one capital letter");

	if(!ContainsLowerCaseLetter(pass))
		throw std::logic_error("The password must contains at least one lower case letter");

	if (!ContainsSpecialSymbols(pass))
		throw std::logic_error("The password must contains at least one special symbol: '@', '#', '-', '_'");
}