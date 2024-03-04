#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cstddef>
#include <iostream>


//C is the capacity of the hashtable
//Best case: Theta(C)
// The best case occurs when the size of the hash table (C)is small or when the initialization 
//of the hash table is already completed with NULL values

//Worst case: Theta(C)
// Same as the best case, the worst case occurs when the size of the hash table (C) is small or
// when the initialization of the hash table is already completed with NULL values

//Total complexity: Theta(C)
//Total complexity is Theta(C) because the best case and the worst case are the same

SortedBag::SortedBag(Relation r) 
{
	this->r = r;
	this->m = 127; // we will use a hash table of 127 positions
	this->nr_elements = 0;

	this->hashTable = new struct Node*[this->m];

	for (int i=0;i< this->m;i++)
		this->hashTable[i] = NULL;
}

//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
//The worst case occurs when the calculation k % aux and the conditional check if (m < 0) take constant time
TComp SortedBag::h(TComp k) const// we calculate the position in the hash table
{
	int m;
	int aux = this->m;
	m = k % aux;
	if(m<0)
		return m+aux;
	return m;
}



//Best case: Theta(N)	
// The best case occurs when the current hash table is already at maximum capacity (this->m) and no resizing is needed

//Worst case: O(N+N^2)
// The worst case occurs when resizing is required, and the current hash table contains N elements
//The function needs to iterate through the existing hash table, delete all nodes, create a new hash table, and re-add all elements

//Total complexity: O(N+N^2)
//Total complexity is O(N) because the worst case is the same as the total complexity
void SortedBag::resize()
{
	this->m= this->m * 2;
	TComp* copy_elements = new TComp[this->nr_elements];// we create a copy of the elements
	int *copy_frequencies = new int[this->nr_elements]; // we create a copy of the frequencies
	int k = 0, i = 0;
	for (i = 0; i < this->m / 2; i++)// we go through the hash table
	{
		struct Node* current = this->hashTable[i];//we go through the list
		while(current!= NULL)// we copy the elements and the frequencies
		{
			copy_elements[k] = current->elem;// we copy the elements
			copy_frequencies[k++] = current->freq;// we copy the frequencies
			current = current->next;// we go to the next element
		}
	}
	for (i = 0; i < this->m / 2; i++)
	{
		struct Node* current = this->hashTable[i]; // we go through the list
		while (current != NULL)
		{
			struct Node* next_node=current->next;// we save the next node
			delete current;// we delete the current node
			current = next_node;// we go to the next node
		}
	}
	delete[] this->hashTable;// we delete the hash table

	this->nr_elements = 0;
	this->hashTable = new struct Node*[this->m];// we create a new hash table

	for (i = 0; i < this->m; i++)// we initialize the hash table
		this->hashTable[i] = NULL;

	for (i = 0; i < k; i++)// we add the elements and the frequencies
		for (int j = 0; j < copy_frequencies[i]; j++)
			this->add(copy_elements[i]);

	delete[] copy_elements;// we delete the copy of the elements
}



//Best case: Theta(1)
// The best case occurs when the element to be added is already present in the sorted bag

//Worst case: O(N)
// The worst case occurs when the element needs to be added at the end of the list or as the first element
// The function needs to iterate through the list to find the correct position for insertion
// The worst case complexity can be broken down into the following steps:
//1.Calculating the load factor : O(1)
//2.Resizing the hash table(if necessary) : O(N)
//3.Calculating the position in the hash table : O(1)
//4.Finding the correct position in the list : O(N)
//5.Inserting the element into the list : O(1)

//Total complexity: O(N)
//The total complexity of the function is the same as the worst case complexity
void SortedBag::add(TComp e) 
{
	auto load_factor =this->nr_elements / this->m;// we calculate the load factor
	if (load_factor >=1)// if the load factor is greater than 1 we resize the hash table
		this->resize();

	TComp poz = this->h(e);// we calculate the position in the hash table
	struct Node* current = this->hashTable[poz];// we go through the list

	while(current!=NULL and e!=current->elem)// we go through the list
		current = current->next;// we go to the next element

	if(current!=NULL)
		current->freq++;// if the element is in the list we increment the frequency
	else
	{
		current=this-> hashTable[poz];// we go through the list
		struct Node* prev_node = NULL;// we create a new node	
		struct Node* new_node = new struct Node;// we create a new node

		new_node->elem = e;
		new_node->freq = 1;

		while (current != NULL and !r(e, current->elem))// we go throgh 
		{
			prev_node= current;
			current = current->next;
		}

		if (prev_node == NULL) // if the element is the first element in the list
		{
			new_node->next = this->hashTable[poz];// we add the element in the list
			this->hashTable[poz] = new_node;// we add the element in the hash table
		}
		else// if the element is not the first element in the list
		{
			new_node->next = current;// we add the element in the list
			prev_node->next = new_node;
		}
	}
	this->nr_elements+=1;// we increment the number of elements
}



//Best case: Theta(1)
// The best case occurs when the element to be removed is not present in the sorted bag

//Worst case: O(N)
// The worst case occurs when the element to be removed is present in the sorted bag.
//The function needs to iterate through the list to find the element and remove it
//The worst case complexity can be broken down into the following steps :
//1.Calculating the position in the hash table : O(1)
//2.Finding the element in the list : O(N)
//3.Removing the element from the list : O(1)

//Total complexity: O(N)
//The total complexity of the function is the same as the worst case complexity
bool SortedBag::remove(TComp e) {
	TComp poz = this->h(e);// we calculate the position in the hash table
	struct Node* current = this->hashTable[poz];
	struct Node* prev_node = NULL;

	while (current != NULL and e != current->elem)// we go through the list
	{
		prev_node = current;
		current = current->next;
	}

	if (current != NULL)// if the element is in the list
	{
		if (current->freq == 1)// if the frequency is 1
		{
			if(prev_node==NULL)// if the element is the first element in the list
				this->hashTable[poz] = this->hashTable[poz]->next;// we delete the element
			else// if the element is not the first element in the list
				prev_node->next = current->next;// we delete the element
		}
		else
			current->freq--;// if the frequency is greater than 1 we decrement the frequency

		this->nr_elements--;// we decrement the number of elements
		return true;
	}
	return false;
}



//Best case: Theta(1)
// The best case occurs when the element to be searched is located at the beginning of the list

//Worst case: O(N)
// The worst case occurs when the element to be searched is not present in the sorted bag or is located at the end of the list

//Total complexity: O(N)
//The total complexity of the function is the same as the worst case complexity
bool SortedBag::search(TComp elem) const 
{
	TComp poz = this->h(elem);// we calculate the position in the hash table
	struct Node* current = this->hashTable[poz];

	while (current != NULL and elem != current->elem)// we go through the list
		current = current->next;// next element
	return (current != NULL);// if the element is in the list return true else return false
}



//Best case: Theta(1)
// The best case occurs when the element to be searched is located at the beginning of the list

//Worst case: O(N)
// The worst case occurs when the element to be counted is not present in the sorted bag or is located at the end of the list

//Total complexity: O(N)
//The total complexity of the function is the same as the worst case complexity
int SortedBag::nrOccurrences(TComp elem) const 
{
	TComp poz = this->h(elem);// position in the hash table
	struct Node* current = this->hashTable[poz];

	while (current != NULL and elem != current->elem)// we go through the list
		current = current->next;// next element

	if (current != NULL)// if the element is in the list
		return current->freq;// return the frequency
	return 0;// if the element is not in the list return 0
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
int SortedBag::size() const 
{
	return this->nr_elements;
}

//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
bool SortedBag::isEmpty() const 
{
	if (this->nr_elements == 0)
		return true;
	return false;
}

//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
SortedBagIterator SortedBag::iterator() const 
{
	return SortedBagIterator(*this);
}


//Best case: Theta(1)
// The best case occurs when the hash table is empty, i.e., there are no nodes to delete.

//Worst case: O(N)
// The worst case occurs when all positions in the hash table are populated, and each linked list has multiple nodes.
//The function iterates through each position in the hash table and deletes all the nodes in the linked list at that position.

//Total complexity: O(N)
//The total complexity of the function is the same as the worst case complexity
SortedBag::~SortedBag() 
{
	int i = 0;
	for (i = 0; i < this->m / 2; i++) // we go through the hash table
	{
		struct Node* current = this->hashTable[i];// current node
		while (current != NULL)// we go through the list
		{
			struct Node* next_node = current->next;// next node
			delete current;// we delete the current node
			current = next_node;// current node becomes the next node
		}
	}
	delete[] this->hashTable;// we delete the hash table
}


//Best case: Theta(N)
// The best case occurs when there are no elements with multiple occurrences.

//Worst case: O(N)
// The worst case occurs when all elements have multiple occurrences, and the function needs to remove all their occurrences.

//Total complexity: O(N)
//The total complexity of the function is the same as the worst case complexity
int SortedBag::removeAll()
{
	int nr = 0;

	for (int i = 0; i < this->m; i++)// we go through the hash table
	{
		struct Node* current = this->hashTable[i];// current node
		struct Node* prevNode = NULL;// previous node

		while (current != NULL)// we go through the list
		{
			if (current->freq > 1)// if the frequency is >1
			{
				struct Node* nextNode = current->next;// next node

				if (prevNode == NULL)// if the element is the first element in the list
					this->hashTable[i] = nextNode;// we delete the element
				else
					prevNode->next = nextNode;// we delete the element


				nr += current->freq;// we increment the number of elements that we deleted
				this->nr_elements -= current->freq;// we decrement the frequency

				delete current;// we delete the element
				current = nextNode;// we go to the next element


			}
			else// if the frequency is <=1 
			{
				prevNode = current;// we go to the next element
				current = current->next;
			}
		}
	}
	return nr;
}