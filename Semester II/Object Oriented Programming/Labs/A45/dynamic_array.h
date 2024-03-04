#pragma once
#include "domain.h"
#include <string>
#include <cstdlib>

template <class TElement>
class DynamicArray
{
private:
	TElement* elements;
	int size;
	int initial_capacity;
	int capacity;

	void Resize()// resize the dynamic array
	{
		TElement* new_elements;
		this->capacity *= 2;
		new_elements= new TElement[this->capacity];
		for (int i = 0; i < this->size; i++)// copy the elements from the old array to the new one
			new_elements[i] = this->elements[i];
		delete[] this->elements;// delete the old array
		this->elements = new_elements;
	}// \param new_elements the new array we are about to create

	void Clear()// clear the dynamic array
	{
		this->size = 0;
		TElement* new_elements;// create a new array with the initial capacity
		this->capacity = this->initial_capacity;
		new_elements = new TElement[this->capacity];
		for (int i = 0; i < this->size; i++)
			new_elements[i] = this->elements[i];
		delete[] this->elements;
		this->elements = new_elements;
	}// \param new_elements the new array we are about to create
public:
	DynamicArray() {
	}

	DynamicArray(int capacity)//initialize the dynamic array with a given capacity
	{
		this->size = 0;
		this->initial_capacity = capacity;
		this->capacity = capacity;
		this->elements = new TElement[capacity];
	}
	~DynamicArray() {//destructor
		delete[] this->elements;
	}

	void Add(const TElement &element)//add an element
	{// \param element the element we are about to add
		if (this->size == this->capacity)
			Resize();
		this->elements[this->size++] = element;
	}

	void Delete(int poz) {// delete an element from a given position
	// \param poz the position of the element we are about to delete
		if (this->size == 1)
			Clear();
		else
		{
			for (int i = poz; i < this->size - 1; i++)
				this->elements[i] = this->elements[i + 1];
			this->size--;
		}
	}

	void Update(const TElement& element, int poz)// e lement, int poz)// update an element from a given position
	{// \param element the element we are about to update}
		this->elements[poz] = element;
	}

	int GetSize() // return the size of the dynamic array
	{
		return this->size;
	}

	TElement& operator [] (int poz) // return the element from a given position
	{// \param poz the position of the element we are about to return
			return this->elements[poz];
	}

	DynamicArray& operator = (const DynamicArray& other) // assignment operator
	{
		if (this == &other)
			return *this;
		if (other.capacity == 0)
			Clear();// if the other array is empty, clear the current array

		this->capacity= other.capacity/2;// create a new array with the same capacity as the other array
		Resize();// resize the current array

		memcpy(this->elements, other.elements, sizeof(TElement)*other.capacity);// copy the elements from the other array to the current one
		return *this;
	}// \param other the dynamic array we are about to copy
};
