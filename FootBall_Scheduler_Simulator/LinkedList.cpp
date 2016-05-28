#include "LinkedList.h"

template<class T>
void LinkedList<T>::add(T d)
{
	Node<T>* new_tail = new Node<T>(d);
	tail->next = new_tail;
	tail = new_tail;
	mySize++;
}


template<class T>
void LinkedList<T>::remove(int pos)
{
	if (isEmpty())
	{
		return;
	}
	Node<T>* current = head;
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
		if (current == NULL) {
			//cout << "Error : Index Out Of Bound." << endl;
			return;
		}

	}
	Node<T>* old_next = current->next;
	current->next = old_next->next;
	mySize--;
}

template<class T>
T LinkedList<T>::get(int pos)
{
	if (isEmpty())
	{
		return NULL;
	}
	Node<T>* current = head;
	for (int i = 0; i <= pos; i++)
	{
		current = current->next;
		if (current == NULL) {
			//cout << "Error : Index Out Of Bound." << endl;
			return NULL;
		}
	}
	return current->val;
}

template<class T>
std::vector<T> LinkedList<T>::getList()
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

template<class T>
std::ostream & operator<<(std::ostream & os, LinkedList<T>& list)
{
	std::vector<T> vec = list.getList();

	while (!vec.empty()) {
		T val = vec.back();
		os << *(ptr(val)) << " " << endl;
		vec.pop_back();
	}
	return os;
}
