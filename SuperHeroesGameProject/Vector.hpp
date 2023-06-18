#pragma once
#include <stdexcept>

template <typename T>
class Vector {
private:
	T* data;
	unsigned capacity = 0;
	unsigned count = 0;

	void moveFrom(Vector&& other);
	void copyFrom(const Vector& other);
	void free();
	void resize();

public:
	Vector();
	Vector(unsigned capacity);
	Vector(const Vector& other);
	Vector(Vector&& other);
	Vector<T>& operator=(const Vector& other);
	Vector<T>& operator=(Vector&& other);
	~Vector();

	unsigned GetCount() const;
	void AddElement(const T& obj);
	void AddElement(T&& obj);
	void RemoveElement(int index);
	void Swap(T& first, T& second);
	const T& operator[](int index) const;
	T& operator[](int index);
};

template<typename T>
Vector<T>::Vector() : Vector(4) {}

template<typename T>
Vector<T>::Vector(unsigned capacity) {
	this->capacity = capacity;
	data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
	copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector&& other) {
	moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector() {
	free();
}

template<typename T>
unsigned Vector<T>::GetCount() const {
	return count;
}

template<typename T>
void Vector<T>::AddElement(const T& obj) {
	if (count == capacity)
		resize();

	data[count++] = obj;
}

template<typename T>
void Vector<T>::AddElement(T&& obj){
	if (count == capacity)
		resize();

	data[count++] = std::move(obj);
}

template<typename T>
void Vector<T>::RemoveElement(int index) {
	if (index < 0 || index >= count)
		throw std::out_of_range("The index is out of range");

	for (int i = index; i < count - 1; i++)
		data[i] = data[i + 1];
	--count;
}

template<typename T>
void Vector<T>::Swap(T& first, T& second){
	T temp = std::move(first);
	first = std::move(second);
	second = std::move(temp);
}

template<typename T>
const T& Vector<T>::operator[](int index) const {
	if (index < 0 || index >= count)
		throw std::out_of_range("The index is out of range");

	return data[index];
}

template<typename T>
T& Vector<T>::operator[](int index) {
	if (index < 0 || index >= count)
		throw std::out_of_range("The index is out of range");

	return data[index];
}

template<typename T>
void Vector<T>::moveFrom(Vector&& other) {
	data = other.data;
	capacity = other.capacity;
	count = other.count;
	other.data = nullptr;
	other.capacity = other.count = 0;
}

template<typename T>
void Vector<T>::copyFrom(const Vector& other) {
	capacity = other.capacity;
	count = other.count;
	data = new T[capacity];
	for (int i = 0; i < count; i++)
		data[i] = other.data[i];
}

template<typename T>
void Vector<T>::free() {
	delete[] data;
	data = nullptr;
}

template<typename T>
void Vector<T>::resize() {
	capacity *= 2;
	T* newData = new T[capacity];
	for (int i = 0; i < count; i++)
		newData[i] = data[i];
	delete[] data;
	data = newData;
}
