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

unsigned SuperHero::GetStrength() const {
	return strength;
}

HeroPosition SuperHero::GetPosition() const{
	return position;
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

void SuperHero::PrintPosition() const{
	if (position == HeroPosition::Attack)
		std::cout << "Attack" << std::endl;
	else if(position == HeroPosition::Defense)
		std::cout << "Defense" << std::endl;
}

void SuperHero::PrintPower() const {
	if (power == HeroPower::Earth)
		std::cout << "Earth" << std::endl;
	else if (power == HeroPower::Fire)
		std::cout << "Fire" << std::endl;
	else if (power == HeroPower::Water)
		std::cout << "Water" << std::endl;
}

void SuperHero::PrintAllInfo() const{
	std::cout << "Name: " << firstName << ' ' << lastName << std::endl;
	std::cout << "Nickname: " << nickname << std::endl;
	std::cout << "Type: ";
	PrintPower();
	std::cout << "Strength: " << strength << std::endl;
	std::cout << "Position: ";
	PrintPosition();
}

void SuperHero::PrintDetailedInfo() const{
	std::cout << "Nickname: " << nickname << std::endl;
	std::cout << "Price: " << price << '$' << std::endl;
	std::cout << "Type: ";
	PrintPower();
	std::cout << "Strength: " << strength << std::endl;
}

void SuperHero::PrintUndetailedInfo() const {
	std::cout << nickname << " - ";
	PrintPower();
}

int SuperHero::IsDominating(const SuperHero& other) const{
	if (power == HeroPower::Fire) {
		if (other.power == HeroPower::Fire)
			return 0;
		return (other.power == HeroPower::Earth) ? 1 : -1;
	}
	else if (power == HeroPower::Earth) {
		if (other.power == HeroPower::Water)
			return 1;
		return (other.power == HeroPower::Fire) ? -1 : 0;
	}
	else {
		if (other.power == HeroPower::Fire)
			return 1;
		return (other.power == HeroPower::Earth) ? -1 : 0;
	}
}

int SuperHero::IsStrongerThan(const SuperHero& other, int attackerIncr, int attackedIncr) const{
	if (strength * attackerIncr > other.strength * attackedIncr)
		return 1;

	return (strength * attackerIncr < other.strength * attackedIncr) ? -1 : 0;
}

void SuperHero::ChangePosition(){
	if (position == HeroPosition::Attack)
		position = HeroPosition::Defense;
	else
		position = HeroPosition::Attack;
}

void SuperHero::ReadFromFile(std::ifstream& file){
	firstName.ReadFromFile(file);
	lastName.ReadFromFile(file);
	nickname.ReadFromFile(file);
	file.read((char*)&power, sizeof(power));
	file.read((char*)&strength, sizeof(strength));
	file.read((char*)&price, sizeof(price));
	file.read((char*)&position, sizeof(position));
}

void SuperHero::SaveToFile(std::ofstream& file) const{
	firstName.SaveToFile(file);
	lastName.SaveToFile(file);
	nickname.SaveToFile(file);
	file.write((const char*)&power, sizeof(power));
	file.write((const char*)&strength, sizeof(strength));
	file.write((const char*)&price, sizeof(price));
	file.write((const char*)&position, sizeof(position));
}
