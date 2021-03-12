#pragma once

#include <string>

using namespace std;

template <typename T>
struct Node {
	T val;
	Node* urm;
	Node(T v) : val{v}, urm{nullptr} {};
	Node(T v, Node* urm) : val{v}, urm{urm} {};
};


template <typename T>
class MyListIterator;

template <typename T>
class MyList {

	Node<T>* cap;

	void elibereazaNoduri();

	Node<T>* copieaza(Node<T>* current);

public:


	MyList() : cap{nullptr} {};


	MyList(const MyList& ot);


	void operator=(const MyList& ot);


	~MyList();


	size_t size() const;

	void addInceput(T v);

	void push_back(T v);

	T& first() const;

	MyListIterator<T> begin() const;


	MyListIterator<T> end() const;


	T& operator[](size_t poz);
};


template <typename T>
MyList<T>::MyList(const MyList& ot) {
	cap = copieaza(ot.cap);
}


template <typename T>
void MyList<T>::operator=(const MyList& ot) {
	elibereazaNoduri();
	cap = copieaza(ot.cap);
}


template <typename T>
MyList<T>::~MyList() {
	elibereazaNoduri();
}


template <typename T>
Node<T>* MyList<T>::copieaza(Node<T>* current) {
	if (current == nullptr) {
		return nullptr;
	}
	auto n = new Node<T>{current->val};
	n->urm = copieaza(current->urm);
	return n;
}

template <typename T>
void MyList<T>::addInceput(T v) {
	Node<T>* n = new Node<T>{v, cap};
	cap = n;
}

template <typename T>
void MyList<T>::push_back(T v) {
	auto nCurent = cap;
	while (nCurent != nullptr && nCurent->urm != nullptr) {
		nCurent = nCurent->urm;
	}

	if (nCurent == nullptr) {
		cap = new Node<T>{v, nullptr};
	}
	else {
		nCurent->urm = new Node<T>{v, nullptr};
	}
}

template <typename T>
size_t MyList<T>::size() const {
	auto nCurent = cap;
	int lg = 0;
	while (nCurent != nullptr) {
		lg++;
		nCurent = nCurent->urm;
	}
	return lg;
}


template <typename T>
T& MyList<T>::operator[](size_t poz) {
	auto nCurent = cap;
	size_t lg = 0;
	while (lg < poz) {
		lg++;
		nCurent = nCurent->urm;
	}
	return nCurent->val;
}

template <typename T>
T& MyList<T>::first() const {
	return cap->val;
}


template <typename T>
void MyList<T>::elibereazaNoduri() {
	auto nCurent = cap;
	while (nCurent != nullptr) {
		auto aux = nCurent->urm;
		delete nCurent;
		nCurent = aux;
	}
	cap = nullptr;
}

template <typename T>
class MyListIterator {
	Node<T>* current;
public:
	MyListIterator(Node<T>* c) : current{c} {}

	bool operator!=(const MyListIterator& ot);


	void operator++();

	T& operator*();
};


template <typename T>
MyListIterator<T> MyList<T>::begin() const {
	return MyListIterator<T>{cap};
}


template <typename T>
MyListIterator<T> MyList<T>::end() const {
	return MyListIterator<T>{nullptr};
}


template <typename T>
bool MyListIterator<T>::operator!=(const MyListIterator& ot) {
	return current != ot.current;
}


template <typename T>
void MyListIterator<T>::operator++() {
	current = current->urm;
}


template <typename T>
T& MyListIterator<T>::operator*() {
	return current->val;
}
