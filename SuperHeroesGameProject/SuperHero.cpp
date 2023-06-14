#include "SuperHero.h"
#include "HelperFunctions.h"

SuperHero::SuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price) {
	SetFirstName(firstName);
	SetLastName(lastName);
	SetNickname(nickname);
	SetHeroPower(power);
	SetStrength(strength);
	SetPrice(price);
}

SuperHero::SuperHero(SuperHero&& obj){
	firstName = std::move(obj.firstName);
	lastName = std::move(obj.lastName);
	nickname = std::move(obj.nickname);
	power = obj.power;
	strength = obj.strength;
	price = obj.price;
	position = obj.position;
}

SuperHero::SuperHero(const SuperHero& other){
	firstName = other.firstName;
	lastName = other.lastName;
	nickname = other.nickname;
	power = other.power;
	strength = other.strength;
	price = other.price;
	position = other.position;
}

const char* SuperHero::GetNickname() const{
	return nickname.c_str();
}

double SuperHero::GetPrice() const{
	return price;
}

void SuperHero::SetFirstName(const char* name) {
	IsNameValid(name);

	firstName = name;
}

void SuperHero::SetLastName(const char* name) {
	IsNameValid(name);

	lastName = name;
}

void SuperHero::SetNickname(const char* name) {
	if (!name)
		throw std::invalid_argument("The nickname doesn't exist");

	nickname = name;
}

void SuperHero::SetHeroPower(const char* power) {
	if (power == nullptr)
		throw std::invalid_argument("The power doesn't exist");

	if (!strcmp(power, "Earth"))
		this->power = HeroPower::Earth;
	else if (!strcmp(power, "Fire"))
		this->power = HeroPower::Fire;
	else if (!strcmp(power, "Water"))
		this->power = HeroPower::Water;
	else
		throw std::invalid_argument("There is no such power");
}

void SuperHero::SetStrength(int strength) {
	if (strength < 0)
		throw std::logic_error("The strength cannot be less than 0");

	this->strength = strength;
}

void SuperHero::SetPrice(double price) {
	if (price < 0)
		throw std::invalid_argument("The price cannot be less than 0");

	this->price = price;
}

void SuperHero::SetHeroPosition(HeroPosition position) {
	this->position = position;
}

void SuperHero::PrintPower() const {
	if (power == HeroPower::Earth)
		std::cout << "Earth" << std::endl;
	else if (power == HeroPower::Fire)
		std::cout << "Fire" << std::endl;
	else if (power == HeroPower::Water)
		std::cout << "Water" << std::endl;
}

void SuperHero::PrintDetailedInfo() const{
	std::cout << "Name: " << firstName << ' ' << lastName << std::endl;
	std::cout << "Price: " << price << '$' << std::endl;
	std::cout << "Type: ";
	PrintPower();
	std::cout << "Strength: " << strength << std::endl;
}

void SuperHero::PrintUndetailedInfo() const {
	std::cout << nickname << " - ";
	PrintPower();
}
