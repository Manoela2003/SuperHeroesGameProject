#include <iostream>
#include "SuperHeroesGame.h"

void StartMenu() {
	std::cout << "~~~~~MENU~~~~~" << std::endl;
	std::cout << "1. Log in as administrator" << std::endl;
	std::cout << "2. Log in as player" << std::endl;
	std::cout << "3. Exit" << std::endl;
}

void LogInInput(char* username, char* password) {
	std::cout << "Enter username: ";
	std::cin.getline(username, buffer_Max_Size);
	std::cout << "Enter password: ";
	std::cin.getline(password, buffer_Max_Size);
}

void AdministratorLogIn(const SuperHeroesGame& game, bool& isLoggedIn) {
	char username[buffer_Max_Size];
	char password[buffer_Max_Size];
	LogInInput(username, password);
	try {
		if (game.LogInAsAdministrator(username, password)) {
			std::cout << "You have logged in successfully!" << std::endl;
			isLoggedIn = true;
		}
		else
			std::cout << "Wrong username or password! Try again!" << std::endl;
	}
	catch (std::invalid_argument& arg) {
		std::cout << arg.what() << std::endl;
	}
}

void PlayerLogIn(const SuperHeroesGame& game, bool& isLoggedIn) {
	char username[buffer_Max_Size];
	char password[buffer_Max_Size];
	LogInInput(username, password);
	try {
		if (game.LogInAsPlayer(username, password)) {
			std::cout << "You have logged in successfully!" << std::endl;
			isLoggedIn = true;
		}
		else
			std::cout << "Wrong username or password! Try again!" << std::endl;
	}
	catch (std::invalid_argument& arg) {
		std::cout << arg.what() << std::endl;
	}
}

void CheckCommand(char* command) {
	while (command[0] < '1' || command[0] > '3' || command[1] != '\0') {
		std::cout << "Wrong command! Choose a number between 1 and 3: ";
		std::cin.getline(command, buffer_Max_Size);
	}
}

bool HasLoggedIn(const SuperHeroesGame& game) {
	bool isLoggedIn = false;

	while (!isLoggedIn) {

		StartMenu();

		char command[buffer_Max_Size];
		std::cin.getline(command, buffer_Max_Size);
		CheckCommand(command);

		switch (command[0]) {
		case '1':
			AdministratorLogIn(game, isLoggedIn);
			break;
		case '2':
			PlayerLogIn(game, isLoggedIn);
			break;
		case '3':
			std::cout << "Goodbye!";
			return false;
		}
		std::cout << std::endl;
	}
	return true;
}

int main()
{
	SuperHeroesGame game;
	if (HasLoggedIn(game)) {
		if (game.IsPlayerLogged()) {

		}
		else if (game.IsAdministratorLogged()) {

		}
	}
	
}
