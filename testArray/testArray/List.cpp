// List.cpp - Implementation of List ADT using Array

#include "List.h"  // header file


// constructor
List::List()
{
	size = 0;
}

// add a new item to the back of the list (append)
bool List::add(ItemType newItem)
{
	bool success = size < MAX_SIZE;
	if (success)
	{
		items[size] = newItem; // add to the end of the list
		size++;                // increase the size of the list by one
	}
	return success;
}

// add a new item at a specified position in the list (insert)
bool List::add(int index, ItemType newItem)
{
	bool success = (index >= 1) && (index <= size + 1) && (size < MAX_SIZE);
	if (success)
	{  // make room for new item by shifting all items at
		// positions >= index toward the end of the
		// List (no shift if index == size + 1)
		for (int pos = size; pos >= index; pos--)
			items[pos] = items[pos - 1];
		// insert new item
		items[index - 1] = newItem;
		size++;  // increase the size of the list by one
	}
	return success;
}

// remove an item at a specified position in the list
void List::remove(int index)
{
	bool success = (index >= 1) && (index <= size);
	if (success)
	{  // delete item by shifting all items at positions >
		// index toward the beginning of the list
		// (no shift if index == size)
		for (int fromPosition = index + 1; fromPosition <= size; fromPosition++)
			items[fromPosition - 2] = items[fromPosition - 1];
		size--;  // decrease the size of the list by one
	}

}

// get an item at a specified position of the list (retrieve)
ItemType List::get(int index)
{
	ItemType dataItem;
	bool success = (index >= 1) && (index <= size);
	if (success)
		dataItem = items[index - 1];

	return dataItem;
}

// check if the list is empty
bool List::isEmpty()
{
	return size == 0;
}

// check the size of the list
int List::getLength()
{
	return size;
}


