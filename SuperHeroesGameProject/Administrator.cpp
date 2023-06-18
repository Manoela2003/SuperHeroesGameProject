#include "Administrator.h"

Administrator::Administrator(const char* firstName, const char* lastName, const char* username, const char* password) : User(firstName, lastName, username, password) {}

Administrator::Administrator(const char* firstName, const char* lastName, const char* email, const char* username, const char* password) : User(firstName, lastName, email, username, password) {}

void Administrator::PrintInfo() const {
	PrintName();
	PrintEmail();
}