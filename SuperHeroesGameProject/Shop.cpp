#include "Shop.h"

static void PrintDashes(int dashesCount) {
	for (int i = 0; i < dashesCount; i++)
		std::cout << '-';
	std::cout << std::endl;
}

int Shop::GetCountOfOldHeroes() const{
	return oldHeroes.GetCount();
}

int Shop::GetCount() const{
	return superHeroes.GetCount();
}

bool Shop::IsShopEmpty() const {
	return superHeroes.GetCount() == 0;
}

void Shop::AddNewSuperHero(SuperHero&& other){
	superHeroes.AddElement(new SuperHero(std::move(other)));
}

void Shop::AddNewSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price) {
	superHeroes.AddElement(new SuperHero(firstName, lastName, nickname, power, strength, price));
}

void Shop::AddOldSuperHero(const SuperHero& other){
	oldHeroes.AddElement(new SuperHero(other));
}

bool Shop::PrintSuperHeroes() const {
	if (IsShopEmpty())
		return false;

	for (int i = 0; i < superHeroes.GetCount(); i++) {
		superHeroes[i]->PrintDetailedInfo();
		PrintDashes(15);
	}
	return true;
}

bool Shop::PrintOldSuperHeroes() const{
	if (oldHeroes.GetCount() == 0)
		return false;

	for (int i = 0; i < oldHeroes.GetCount(); i++) {
		std::cout << i + 1 << ". ";
		oldHeroes[i]->PrintDetailedInfo();
		PrintDashes(15);
	}
	return true;
}

void Shop::RemoveSuperHero(const SuperHero& hero){
	for (int i = 0; i < superHeroes.GetCount(); i++) {
		if (!strcmp(superHeroes[i]->GetNickname(), hero.GetNickname())) {
			superHeroes.RemoveElement(i);
			return;
		}
	}
}

SuperHero Shop::FindSuperHero(const char* nickname) const{
	if (nickname == nullptr)
		throw std::invalid_argument("The nickname doesn't exist");

	for (int i = 0; i < superHeroes.GetCount(); i++) {
		if (!strcmp(nickname, superHeroes[i]->GetNickname()))
			return *superHeroes[i];
	}

	throw std::logic_error("There is no such SuperHero");
}

SuperHero& Shop::GetOldSuperHero(int index){
	if (index < 0 || index > oldHeroes.GetCount())
		throw std::out_of_range("Out of range");

	return *oldHeroes[index];
}

void Shop::RemoveOldSuperHero(int index){
	if (index < 0 || index > oldHeroes.GetCount())
		throw std::out_of_range("Out of range");

	oldHeroes.RemoveElement(index);
}

int Shop::IndexOfSuperHero(const char* nickname) const{
	if (nickname == nullptr)
		throw std::invalid_argument("The nickname doesn't exist");

	for (int i = 0; i < superHeroes.GetCount(); i++) {
		if (!strcmp(nickname, superHeroes[i]->GetNickname()))
			return i;
	}
	return -1;
}

void Shop::ReadFromFile(std::ifstream& file){
	unsigned count = 0;
	file.read((char*)&count, sizeof(count));
	for (int i = 0; i < count; i++) {
		SuperHero hero;
		hero.ReadFromFile(file);
		superHeroes.AddElement(new SuperHero(std::move(hero)));
	}
	file.read((char*)&count, sizeof(count));
	for (int i = 0; i < count; i++) {
		SuperHero hero;
		hero.ReadFromFile(file);
		oldHeroes.AddElement(new SuperHero(std::move(hero)));
	}
}

void Shop::SaveToFile(std::ofstream& file) const{
	unsigned count = GetCount();

	file.write((const char*)&count, sizeof(count));

	for (int i = 0; i < count; i++)
		superHeroes[i]->SaveToFile(file);

	count = GetCountOfOldHeroes();
	file.write((const char*)&count, sizeof(count));

	for (int i = 0; i < count; i++)
		oldHeroes[i]->SaveToFile(file);
}
