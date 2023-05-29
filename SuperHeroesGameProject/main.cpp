#include <iostream>
#include "SuperHeroesGame.h"

void PrintStartMenu() {
	std::cout << "~~~~~MENU~~~~~" << std::endl;
	std::cout << "1. Log in as administrator" << std::endl;
	std::cout << "2. Log in as player" << std::endl;
	std::cout << "3. Exit" << std::endl;
}

void LogInInput(char* username, char* password) {
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	std::cin >> password;
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
			std::cout << "Wrong username or password!" << std::endl;
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
			std::cout << "Wrong username or password!" << std::endl;
	}
	catch (std::invalid_argument& arg) {
		std::cout << arg.what() << std::endl;
	}
}

void CheckCommand(char* command, char lastOption) {
	while (command[0] < '1' || command[0] > lastOption || command[1] != '\0') {
		std::cout << "Wrong command! Choose a number between 1 and " << lastOption << ": ";
		std::cin.getline(command, buffer_Max_Size);
	}
}

bool HasLoggedIn(const SuperHeroesGame& game) {
	bool isLoggedIn = false;

	while (!isLoggedIn) {

		PrintStartMenu();

		char command[buffer_Max_Size];
		std::cin.getline(command, buffer_Max_Size);
		CheckCommand(command, '3');

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

void PrintAdministratorOptions() {
	std::cout << "~~~Administrator Menu~~~" << std::endl;
	std::cout << "1. Add player or administrator" << std::endl;
	std::cout << "2. Delete player's profile" << std::endl;
	std::cout << "3. Show information about player or administrator" << std::endl;
	std::cout << "4. Add new super heroes to the shop" << std::endl;
	std::cout << "5. Log out" << std::endl;
}

void InputUser(char* firstName, char* lastName, char* username, char* password) {
	std::cout << "Enter first and last name: ";
	std::cin >> firstName >> lastName;
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	std::cin >> password;
}

bool AddPlayer(SuperHeroesGame& game, char* firstName, char* lastName, char* username, char* password) {
	InputUser(firstName, lastName, username, password);
	try {
		game.AddPlayer(firstName, lastName, username, password);
	}
	catch (std::invalid_argument& inv) {
		std::cout << inv.what() << std::endl;
		return false;
	}
	catch (std::logic_error& le) {
		std::cout << le.what() << std::endl;
		return false;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
		return false;
	}
	catch (...) {
		std::cout << "Unknown error!" << std::endl;
		return false;
	}
	return true;
}

bool AddAdministrator(SuperHeroesGame& game, char* firstName, char* lastName, char* username, char* password) {
	InputUser(firstName, lastName, username, password);
	try {
		game.AddAdministrator(firstName, lastName, username, password);
	}
	catch (std::invalid_argument& inv) {
		std::cout << inv.what() << std::endl;
		return false;
	}
	catch (std::logic_error& le) {
		std::cout << le.what() << std::endl;
		return false;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
		return false;
	}
	catch (...) {
		std::cout << "Unknown error!" << std::endl;
		return false;
	}
	return true;
}

void AddPlayerOrAdministrator(SuperHeroesGame& game) {
	std::cout << "1. Add Player" << std::endl;
	std::cout << "2. Add Administrator" << std::endl;

	char firstName[buffer_Max_Size];
	char lastName[buffer_Max_Size];
	char username[buffer_Max_Size];
	char password[buffer_Max_Size];

	char command[buffer_Max_Size];
	std::cin.getline(command, buffer_Max_Size);
	CheckCommand(command, '2');

	switch (command[0]) {
	case '1':
		AddPlayer(game, firstName, lastName, username, password);
		break;
	case '2':
		AddAdministrator(game, firstName, lastName, username, password);
		break;
	}
}

int main()
{
	SuperHeroesGame game;
	game.AddAdministrator("Mebg", "Ewgewg", "aannitoo", "Aniichka@1");
	while (HasLoggedIn(game)) {
		if (game.IsPlayerLogged()) {

		}
		else if (game.IsAdministratorLogged()) {
			bool isSuccessful = false;
			while (!isSuccessful) {
				PrintAdministratorOptions();
				char command[buffer_Max_Size];
				std::cin.getline(command, buffer_Max_Size);
				CheckCommand(command, '5');

				switch (command[0]) {
				case '1':
					AddPlayerOrAdministrator(game);
					break;
				case '2':

				}
			}

		}
	}
}

