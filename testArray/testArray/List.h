// List.h - - Specification of List ADT
#ifndef LIST_H
#define LIST_H

#include<string>
#include<iostream>
using namespace std;
const int MAX_SIZE =10000; // initialize the size of array, not sure what is the exact max
typedef string ItemType;

class List
{
private:
	
	int      size;
	//ItemType *array = new ItemType[size];  Testing dynamic array but failed D:
	ItemType items[MAX_SIZE];
	 

public:

	List::List();
	bool List::add(ItemType newItem);
	bool List::add(int index, ItemType newItem);
	void List::remove(int index);
	ItemType List::get(int index);
	bool List::isEmpty();
	int List::getLength();
	
};
#endif