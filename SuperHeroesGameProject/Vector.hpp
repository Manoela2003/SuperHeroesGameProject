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
	Vector(int capacity);
	Vector(const Vector& other);
	Vector(Vector&& other);
	Vector<T>& operator=(const Vector& other);
	Vector<T>& operator=(Vector&& other);
	~Vector();

	void AddElement(const T& obj);
};

template<typename T>
Vector<T>::Vector() : Vector(4) {}

template<typename T>
Vector<T>::Vector(int capacity) {
	if (capacity <= 0)
		throw std::invalid_argument("The capacity cannot be less than 1!");

	this->capacity = capacity;
	data = new T[capacity];
}

template<typename T>
inline Vector<T>::Vector(const Vector& other){
	copyFrom(other);
}

template<typename T>
inline Vector<T>::Vector(Vector&& other){
	moveFrom(std::move(other));
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& other){
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector&& other){
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
inline Vector<T>::~Vector(){
	free();
}

template<typename T>
inline void Vector<T>::AddElement(const T& obj){
	if (count == capacity)
		resize();

	data[count++] = obj;
}

template<typename T>
inline void Vector<T>::moveFrom(Vector&& other){
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
inline void Vector<T>::free(){
	delete[] data;
}

template<typename T>
inline void Vector<T>::resize(){
	capacity *= 2;
	T* newData = new T[capacity];
	for (int i = 0; i < count; i++)
		newData[i] = data[i];
	delete[] data;
	data = newData;
}
