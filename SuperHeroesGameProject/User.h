#pragma once
#include "String.h"

class User {
protected:
	String firstName;
	String lastName;
	String email;
	String username;
	String password;

public:
	User() = default;
	User(const char* firstName, const char* lastName, const char* username, const char* password);
	User(const char* firstName, const char* lastName, const char* email, const char* username, const char* password);

	void SetFirstName(const char* name);
	void SetLastName(const char* name);
	void SetEmail(const char* email);
	void SetUsername(const char* username);
	void SetPassword(const char* password);

	virtual void PrintInfo() const = 0;
        // Add abstract destructor
	bool IsEmailEmpty() const;
};
