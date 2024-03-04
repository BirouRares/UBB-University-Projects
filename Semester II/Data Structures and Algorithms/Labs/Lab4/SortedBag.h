#pragma once
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;
//hashtable with separate chaining in which the elements are stored. If an element appears in multiple times, it will be stored multiple times in the hashtable
typedef TComp(*TFunction)(TComp);
struct Node 
{
	TElem elem; // the element stored on the current position
	int freq; // the frequency of the element
	struct Node* next; // the next element in the list
};

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	// elements are stored in a hashtable (struct Node** hashtable) using separate chaining.
	struct Node** hashTable; // the hash table
	int m;
	int nr_elements; // the number of elements in the hash table
	TComp h(TComp) const; // the hash function
	Relation r; // the relation used to order the elements

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	void resize(); 
	// resizes the hash table

	//removes completely all elements that appear multiple times int he SortedBag(all their occurrences are removed)
	//returns the number of removed elements
	int removeAll();

	//destructor
	~SortedBag();
};