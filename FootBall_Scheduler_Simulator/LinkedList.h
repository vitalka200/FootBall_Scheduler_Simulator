#ifndef __LLIST_H
#define __LLIST_H

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Node
{
private:
	template<typename T>
	friend class LinkedList;

	T val;
	Node<T>* next;
public:
	Node<T>(T input) : val(input), next(NULL) {}
	Node<T>() : val(NULL), next(NULL) {}
	Node<T>& operator=(Node<T>&);
	~Node<T>() {}
};


template<class T>
T* ptr(T& obj) { return &obj; }

template<class T>
T* ptr(T* obj) { return obj; }


template<class T>
class LinkedList
{
friend  std::ostream;
private:
	Node<T> *head;
	Node<T> *tail;
	int mySize;

public:
	// c-tors, d-tors
	LinkedList()  { head = new Node<T>(); tail = new Node<T>(); head = tail; mySize = 0; }
	~LinkedList() { }

	void add(T d);

	void remove(int pos);

	T get(int pos);

	bool isEmpty() { return mySize == 0; }

	int size()     { return mySize;	}

	std::vector<T> getList();



	friend std::ostream& operator<<(std::ostream& os, LinkedList<T>& list);
};

#endif