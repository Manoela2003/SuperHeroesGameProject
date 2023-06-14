#include <iostream>
#include "SuperHeroesGame.h"
#include <stdlib.h>

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

void AddPlayer(SuperHeroesGame& game, char* firstName, char* lastName, char* username, char* password) {
	InputUser(firstName, lastName, username, password);
	try {
		if (game.AddPlayer(firstName, lastName, username, password))
			std::cout << "Player successfully added!" << std::endl;
		else
			std::cout << "Only administrators can add new players!" << std::endl;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error!" << std::endl;
	}
}

void AddAdministrator(SuperHeroesGame& game, char* firstName, char* lastName, char* username, char* password) {
	InputUser(firstName, lastName, username, password);
	try {
		if (game.AddAdministrator(firstName, lastName, username, password)) {
			std::cout << "Administrator successfully added!" << std::endl;
		}
		else {
			std::cout << "Only administrators can add new ones!" << std::endl;
		}
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error!" << std::endl;
	}
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

void DeletePlayersProfile(SuperHeroesGame& game) {
	char username[buffer_Max_Size];
	std::cout << "Enter player's username: ";
	std::cin >> username;

	try {
		if (game.DeletePlayer(username))
			std::cout << username << " deleted successfully!" << std::endl;
		else
			std::cout << "There is no player with such username!" << std::endl;
	}
	catch (std::invalid_argument& inv) {
		std::cout << inv.what() << std::endl;
	}
	catch (std::logic_error& le) {
		std::cout << le.what() << std::endl;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}

void PrintAllPlayersInfo(const SuperHeroesGame& game) {
	try {
		game.PrintAllPlayers();
	}
	catch (std::logic_error& le) {
		std::cout << le.what() << std::endl;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}

void PrintSpecificPlayerInfo(const SuperHeroesGame& game) {
	std::cout << "Enter player's username: ";
	char username[buffer_Max_Size];
	std::cin >> username;
	try {
		if (!game.PrintSpecificPlayer(username)) {
			std::cout << "There is no player with such username!" << std::endl;
		}
	}
	catch (std::logic_error& le) {
		std::cout << le.what() << std::endl;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}

void ShowInfoOfPlayer(const SuperHeroesGame& game) {
	std::cout << "1. Show all players" << std::endl;
	std::cout << "2. Show information about specific player" << std::endl;

	char command[buffer_Max_Size];
	std::cin.getline(command, buffer_Max_Size);
	CheckCommand(command, '2');

	switch (command[0]) {
	case '1':
		PrintAllPlayersInfo(game);
		break;

	case '2':
		PrintSpecificPlayerInfo(game);
		break;
	}
}

void PrintAllAdminsInfo(const SuperHeroesGame& game) {
	try {
		game.PrintAllAdmins();
	}
	catch (std::logic_error& le) {
		std::cout << le.what() << std::endl;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}

void PrintSpecificAdminInfo(const SuperHeroesGame& game) {
	std::cout << "Enter administrator's first name: ";
	char firstName[buffer_Max_Size];
	std::cin >> firstName;
	try {
		if (!game.PrintSpecificAdministrator(firstName))
			std::cout << "There is no administrator with such username!" << std::endl;
	}
	catch (std::logic_error& le) {
		std::cout << le.what() << std::endl;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}
}

void ShowInfoOfAdministrator(const SuperHeroesGame& game) {
	std::cout << "Show all administrators" << std::endl;
	std::cout << "Show information about specific administrator" << std::endl;

	char command[buffer_Max_Size];
	std::cin.getline(command, buffer_Max_Size);
	CheckCommand(command, '2');

	switch (command[0]) {
	case '1':
		PrintAllAdminsInfo(game);
		break;

	case '2':
		PrintSpecificAdminInfo(game);
		break;
	}
}

void ShowInfoOfPlayerOrAdmin(const SuperHeroesGame& game) {
	std::cout << "1. Show info about player" << std::endl;
	std::cout << "2. Show info about administrator" << std::endl;

	char command[buffer_Max_Size];
	std::cin.getline(command, buffer_Max_Size);
	CheckCommand(command, '2');

	switch (command[0]) {
	case '1':
		ShowInfoOfPlayer(game);
		break;
	case '2':
		ShowInfoOfAdministrator(game);
		break;
	}
}

void InputHero(char* firstName, char* lastName, char* nickname, char* power, int strength, double price) {
	std::cout << "Enter name: ";
	std::cin >> firstName, lastName;
	std::cout << "Enter nickname: ";
	std::cin >> nickname;
	std::cout << "Enter type of power: ";
	std::cin >> power;
	std::cout << "Enter strength: ";
	std::cin >> strength;
	std::cout << "Enter price: ";
	std::cin >> price;
}

void AddHeroToTheShop(SuperHeroesGame& game) {
	char firstName[buffer_Max_Size], lastName[buffer_Max_Size], nickname[buffer_Max_Size], power[buffer_Max_Size];
	int strength = 0;
	double price = 0;
	InputHero(firstName, lastName, nickname, power, strength, price);
	try {
		if (game.AddSuperHero(firstName, lastName, nickname, power, strength, price))
			std::cout << "Hero successfully added!" << std::endl;
		else
			std::cout << "Only administrators can add new heroes!" << std::endl;
	}
	catch (std::exception& exc) {
		std::cout << exc.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error!" << std::endl;
	}
}

void PrintPlayerOptions() {
	std::cout << "~~~Player Menu~~~" << std::endl;
	std::cout << "1. Print other players' info" << std::endl;
	std::cout << "2. Print the ranking" << std::endl;
	std::cout << "3. Visit the shop" << std::endl;
	std::cout << "4. Attack a Superhero" << std::endl;
	std::cout << "5. Show balance" << std::endl;
	std::cout << "6. Change position of a Superhero" << std::endl;
	std::cout << "7. Delete your account" << std::endl;
	std::cout << "8. Log out" << std::endl;
}

void VisitShop(SuperHeroesGame& game) {
	if (!game.PrintShop()) {
		std::cout << "The shop is empty" << std::endl;
		return;
	}

	std::cout << "If you want to go to the main menu type 'back'" << std::endl;
	std::cout << "Enter Superhero name you wish to buy: ";

	char input[buffer_Max_Size];
	std::cin.getline(input, buffer_Max_Size);
	if (!strcmp(input, "back"))
		return;

	if (game.BuySuperHero(input)) {
		std::cout << input << " bought successfully!" << std::endl;
		game.PrintPlayerBalance();
	}
	else {
		std::cout << "Insufficent balance" << std::endl;
	}
}

void AttackSuperHero(SuperHeroesGame& game) {
	game.PrintOtherPlayersInfo();
	std::cout << "Enter username of a player you wish to attack: ";
	char username[buffer_Max_Size];
	std::cin.getline(username, buffer_Max_Size);

	int playerIndex = game.IndexOfPlayer(username);
	if (playerIndex != -1) {
		std::cout << "Enter Superhero you want to use for the attack: ";
		char hero[buffer_Max_Size];
		std::cin.getline(hero, buffer_Max_Size);
		int indexOfAttacker = game.IndexOfSuperHero(hero);

		if (indexOfAttacker == -1) {
			std::cout << "There is no such Superhero" << std::endl;
			return;
		}

		std::cout << "Enter Superhero you want to attack or type 'random': ";
		std::cin.getline(hero, buffer_Max_Size);
		int indexOfAttacked = game.IndexOfSuperHero(hero, playerIndex);

		if (!strcmp(hero, "random")) {
			srand(time(0));
			indexOfAttacked = rand() % game.GetCountOfSuperHeroes(playerIndex);
		}
		else
			indexOfAttacked = game.IndexOfSuperHero(hero);

		if (indexOfAttacked == -1) {
			std::cout << "There is no such Superhero" << std::endl;
			return;
		}

		if (game.Attack(playerIndex, indexOfAttacker, indexOfAttacked))
			std::cout << "You won!" << std::endl;
		else
			std::cout << "You lost!" << std::endl;
	}
	else {
		std::cout << "There is no such player!" << std::endl;
	}
}

void ChangePositionOfSuperHero(SuperHeroesGame& game) {
	std::cout << "Enter nickname of a Superhero you wish to change position: ";
	char nickname[buffer_Max_Size];
	std::cin.getline(nickname, buffer_Max_Size);
	if (game.ChangePositionOfSuperHero(nickname))
		std::cout << "Position changed successfully!" << std::endl;
	else
		std::cout << "There is no such Superhero!" << std::endl;
}

void DeleteAccount(SuperHeroesGame& game) {
	std::cout << "If you want to delete your account type 'delete': ";
	char input[buffer_Max_Size];
	std::cin.getline(input, buffer_Max_Size);
	if (!strcmp(input, "delete")) {
		std::cout << "Your account is being deleted!" << std::endl;
		game.DeleteOwnProfile();
	}
	else
		std::cout << "Wrong command. Your account will NOT be deleted!" << std::endl;
}

void LogOut(const SuperHeroesGame& game) {
	try {
		game.LogOut();
		std::cout << "Logging out..." << std::endl;
	}
	catch (std::logic_error& le) {
		std::cout << le.what() << std::endl;
	}
}

int main()
{
	SuperHeroesGame game;
	game.AddAdministrator("Mebg", "Ewgewg", "aannitoo", "Aniichka@1");
	while (HasLoggedIn(game)) {
		bool isSuccessful = false;
		char command[buffer_Max_Size];
		if (game.IsPlayerLogged()) {
			PrintPlayerOptions();
			std::cin.getline(command, buffer_Max_Size);
			CheckCommand(command, '8');

			switch (command[0])
			{
			case '1':
				game.PrintOtherPlayersInfo();
				break;

			case '2':
				break;

			case '3':
				VisitShop(game);
				break;

			case '4':
				AttackSuperHero(game);
				break;

			case '5':
				game.PrintPlayerBalance();
				break;

			case '6':
				ChangePositionOfSuperHero(game);
				break;

			case '7':
				DeleteAccount(game);
				break;

			case '8':
				LogOut(game);
				break;
			}
		}
		else if (game.IsAdministratorLogged()) {
			PrintAdministratorOptions();
			std::cin.getline(command, buffer_Max_Size);
			CheckCommand(command, '5');

			switch (command[0]) {
			case '1':
				AddPlayerOrAdministrator(game);
				break;

			case '2':
				DeletePlayersProfile(game);
				break;

			case '3':
				ShowInfoOfPlayerOrAdmin(game);
				break;

			case '4':
				AddHeroToTheShop(game);
				break;

			case '5':
				LogOut(game);
				break;
			}
		}
	}
}