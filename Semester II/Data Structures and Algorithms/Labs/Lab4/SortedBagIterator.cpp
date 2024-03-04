#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//N is the number of elements in the container
//Best case: Theta(N^2)
//Worst case: Theta(N^2)
//Total complexity: Theta(N^2)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) 
{
	this->copy_elements=new TComp[b.nr_elements];
	int k = 0,i=0,j=0;
	for (i = 0; i < this->bag.m; i++)// we go through the hash table
	{
		struct Node* current = this->bag.hashTable[i];// we go through the list
		while (current != NULL)// we copy the elements and the frequencies
		{
			for(j=0;j<current->freq;j++)// we copy the elements and the frequencies
				this->copy_elements[k++]=current->elem;// we copy the elements
			current = current->next;// we go to the next element
		}
	}
	for (i = 0; i < this->bag.nr_elements - 1; i++)
		for(j=i+1;j<this->bag.nr_elements;j++)
			if (!this->bag.r(this->copy_elements[i], this->copy_elements[j]))
			{
				//swap(this->copy_elements[i], this->copy_elements[j]);
				int aux = this->copy_elements[i];
				this->copy_elements[i] = this->copy_elements[j];
				this->copy_elements[j] = aux;
			}
	this->copy_current_position = 0;// we set the current position to 0
	int first_elem = this->copy_elements[0];// we take the first element
	this->current_position == this->bag.h(first_elem); 
	this->current = this->bag.hashTable[this->current_position];// we set the current position to the first element
}


//M is the maximum number of distinct elements associated to a key
//Best case: Theta(1)
//Worst case: O(M)
//Total complexity: O(M)
TComp SortedBagIterator::getCurrent() 
{
	if(!this->valid())// if the iterator is not valid we throw an exception
		throw exception();
	this->current_position = this->bag.h(copy_elements[copy_current_position]);// we calculate the position in the hash table
	struct Node* current = this->bag.hashTable[this->current_position];

	while (current != NULL && current->elem != copy_elements[copy_current_position])// we go through the list
		current = current->next;

	this->current=current;// we set the current position to the first element
	return this->current->elem;// we return the current element
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
bool SortedBagIterator::valid() 
{
	return (this->copy_current_position!=this->bag.nr_elements);// we check if the iterator is valid
}



//M is the maximum number of distinct elements associated to a key
//Best case: Theta(1)
//Worst case: O(M)
//Total complexity: O(M)
void SortedBagIterator::next() 
{
	if (!this->valid())// if the iterator is not valid we throw an exception
		throw exception();
	this->copy_current_position++;// we go to the next element

	if (this->copy_elements[this->copy_current_position] != copy_elements[this->copy_current_position - 1])// if the next element is different from the previous one
	{
		this->current_position = this->bag.h(copy_elements[copy_current_position]);// we calculate the position in the hash table
		struct Node* current = this->bag.hashTable[this->current_position];

		while (current != NULL && current->elem != copy_elements[copy_current_position])// we go through the list
			current = current->next;

		this->current = current;// we set the current position to the first element
	}
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
void SortedBagIterator::first() 
{
	this->copy_current_position = 0;// we set the current position to 0
	int first_elem = this->copy_elements[0];// we take the first element
	this->current_position = this->bag.h(first_elem);
	this->current = this->bag.hashTable[this->current_position];// we set the current position to the first element
}

