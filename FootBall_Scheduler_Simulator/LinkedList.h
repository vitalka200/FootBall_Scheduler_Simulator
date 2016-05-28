#ifndef __LLIST_H
#define __LLIST_H

#include <iostream>
#include <vector>
#include <list>
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
	LinkedList() { head = new Node<T>(); tail = new Node<T>(); head = tail; mySize = 0; }
	~LinkedList() { }
	
	// Methods
	bool isEmpty() { return mySize == 0; }
	int size() { return mySize; }

	void add(T d)
	{
		Node<T>* new_tail = new Node<T>(d);
		tail->next = new_tail;
		tail = new_tail;
		mySize++;
	}

	void remove(int pos)
	{
		if (isEmpty()) { return; }

		Node<T>* current = head;
		for (int i = 0; i < pos; i++)
		{
			current = current->next;
			if (current == NULL) { return; }
		}

		Node<T>* old_next = current->next;
		current->next = old_next->next;
		mySize--;
	}

	T get(int pos)
	{
		if (isEmpty()) { return NULL; }

		Node<T>* current = head;
		for (int i = 0; i <= pos; i++)
		{
			current = current->next;
			if (current == NULL) { return NULL;	}
		}
		return current->val;
	}

	std::vector<T> getList()
	{
		std::vector<T> vec;
		Node<T>* current = head;
		current = current->next;
		while (current != NULL) {
			vec.push_back(current->val);
			current = current->next;
		}
		return vec;
	}

	friend std::ostream& operator<<(std::ostream& os, LinkedList<T>& list)
	{
		std::vector<T> vec = list.getList();

		while (!vec.empty()) {
			T val = vec.back();
			os << *(ptr(val)) << " " << endl;
			vec.pop_back();
		}
		return os;
	}

};

#endif