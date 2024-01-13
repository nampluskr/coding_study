#pragma once

#include "node.h"

template<typename T>
struct LinkedListIterative{
	Node<T>* head = nullptr;

	void clear() {}
	Node<T>* find(const T& data) {}
	void insert(const T& data) {}
	void remove(const T& data) {}
};

template<typename T>
struct LinkedListRecursive {
	Node<T>* head = nullptr;

	Node<T>* clear() {}
	Node<T>* find(const T& data) {}
	Node<T>* insert(const T& data) {}
	Node<T>* remove(const T& data) {}
};