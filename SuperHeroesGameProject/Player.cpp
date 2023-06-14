#include "Player.h"

static void PrintSpaces(int spacesCount) {
	for (int i = 0; i < spacesCount; i++)
		std::cout << ' ';
}

Player::Player(const char* firstName, const char* lastName, const char* username, const char* password) : User(firstName, lastName, username, password) {}

Player::Player(const char* firstName, const char* lastName, const char* email, const char* username, const char* password) : User(firstName, lastName, email, username, password) {}

void Player::PrintBalance() const {
	std::cout << "Balance: " << balance << '$' << std::endl;
}

void Player::PrintHeroes() const {
	std::cout << "Heroes: " << std::endl;
	for (int i = 0; i < heroes.GetCount(); i++) {
		PrintSpaces(15);
		std::cout << i + 1 << ". ";
		heroes[i]->PrintUndetailedInfo();
	}
}

bool Player::BuySuperHero(SuperHero& hero) {
	if (balance >= hero.GetPrice()) {
		heroes.AddElement(new SuperHero(std::move(hero)));
		balance -= hero.GetPrice();
		return true;
	}
	return false;
}

void Player::PrintInfo() const {
	PrintName();
	PrintEmail();
	PrintUsername();
}
