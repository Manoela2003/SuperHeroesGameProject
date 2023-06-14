#pragma once
#include "Vector.hpp"
#include "SharedPtr.hpp"

template <typename T>
void SaveVector(const char* fileName, const Vector<SharedPtr<T>>& elements) {
	if (fileName == nullptr)
		throw std::invalid_argument("The file doesn't exist");

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = elements.GetCount();
	file.write((const char*)&count, sizeof(count));
	for (int i = 0; i < count; i++)
		file.write((const char*)&elements[i], sizeof(*elements[i]));

	file.close();
}

template <typename T>
void ReadVector(const char* fileName, Vector<SharedPtr<T>>& elements) {
	if (fileName == nullptr)
		throw std::invalid_argument("The file doesn't exist");

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open())
		throw std::exception("The file couldn't open!");

	unsigned count = 0;
	file.read((char*)&count, sizeof(count));
	Vector<SharedPtr<T>> newVector(count);

	for (int i = 0; i < count; i++)
		file.read((char*)&newVector[i], sizeof(*newVector[i]));

	elements = std::move(newVector);

	file.close();
}
