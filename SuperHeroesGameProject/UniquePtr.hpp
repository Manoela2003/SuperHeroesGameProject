#pragma once

template <typename T>
class UniquePtr {
	T* data = nullptr;

	void free();
	void moveFrom(UniquePtr&& other);
public:
	UniquePtr(const T* data);
	UniquePtr(const UniquePtr& other) = delete;
	UniquePtr<T>& operator=(const UniquePtr& other) = delete;
	UniquePtr(UniquePtr&& other);
	UniquePtr<T>& operator=(UniquePtr&& other);
	const T& operator*() const;
	T& operator*();
	~UniquePtr();
};

template<typename T>
void UniquePtr<T>::free() {
	if (data != nullptr)
		delete data;
}

template<typename T>
void UniquePtr<T>::moveFrom(UniquePtr&& other) {
	data = other.data;
	other.data = nullptr;
}

template<typename T>
UniquePtr<T>::UniquePtr(const T* data) {
	if (data != nullptr)
		this->data = data;
}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) {
	moveFrom(std::move(other));
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
const T& UniquePtr<T>::operator*() const{
	if (data != nullptr)
		return *data;
}

template<typename T>
T& UniquePtr<T>::operator*(){
	if (data != nullptr)
		return *data;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
	free();
}
