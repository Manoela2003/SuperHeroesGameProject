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

int Player::IndexOfSuperHero(const char* nickname) const{
	if (nickname == nullptr)
		throw std::invalid_argument("The nickname doesn't exist");

	for (int i = 0; i < heroes.GetCount(); i++) {
		if (!strcmp(heroes[i]->GetNickname(), nickname))
			return i;
	}
	return -1;
}

void Player::LoseMoney(unsigned amount){
	balance -= amount;
	if (balance < 0)
		balance = 0;
}

void Player::EarnMoney(unsigned amount){
	balance += amount;
}

SharedPtr<SuperHero> Player::GetSuperHero(int index) const{
	return heroes[index];
}

void Player::RemoveSuperHero(const SuperHero& other){
	for (int i = 0; i < heroes.GetCount(); i++) {
		if (!strcmp(other.GetNickname(), heroes[i]->GetNickname())) {
			heroes.RemoveElement(i);
			return;
		}
	}
}

void Player::PrintInfo() const {
	PrintName();
	PrintEmail();
	PrintUsername();
}
