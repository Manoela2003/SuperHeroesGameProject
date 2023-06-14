#include "Shop.h"
#include "FileFunctions.h"

static void PrintDashes(int dashesCount) {
	for (int i = 0; i < dashesCount; i++)
		std::cout << '-';
}

bool Shop::IsShopEmpty() const {
	return superHeroes.GetCount() == 0;
}

void Shop::AddNewSuperHero(const char* firstName, const char* lastName, const char* nickname, const char* power, int strength, double price) {
	superHeroes.AddElement(new SuperHero(firstName, lastName, nickname, power, strength, price));
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

void Shop::ReadFromFile(const char* fileName){
	ReadVector<SuperHero>(fileName, superHeroes);
}

void Shop::SaveToFile(const char* fileName) const{
	SaveVector<SuperHero>(fileName, superHeroes);
}
