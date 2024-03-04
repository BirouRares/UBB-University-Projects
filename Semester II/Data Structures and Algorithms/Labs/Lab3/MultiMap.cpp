#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include <unordered_map>

using namespace std;

//Best case: Theta(1)- when the MultiMap is empty
 

//Worst case: O(N+M)- when the MultiMap has non-empty keys and values,the function iterates through all the keys and values
//The worst case complexity is equal to the sum of the number of keys (N) and the maximum number of values for a key (M).
 

//Total complexity: Theta(N+M)
//On average, the function needs to iterate through all the keys and values to determine the most frequent value. 
MultiMap::MultiMap() 
{
	this->number_of_pairs = 0;
}

//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
TValue MultiMap::mostFrequent() const
{
	if (this->isEmpty())
		return NULL_TVALUE; // Return NULL_TVALUE if the MultiMap is empty

	unordered_map<TValue, int> frequencyMap; // Map that stores the frequency of each value
	int maxFrequency = 0;
	TValue mostFrequentValue = NULL_TVALUE;

	// iterate through all the values in the MultiMap and count their frequencies
	int currentKey = this->keys.head;// currentKey is the first key
	while (currentKey != -1) // iterate through all the keys
	{
		int i = this->keys.nodes[currentKey].info.second.head;// i is the first value of the current key
		while (i != -1) // iterate through all the values of the current key
		{
			TValue value = this->keys.nodes[currentKey].info.second.nodes[i].info;// current value
			frequencyMap[value]++;// count
			if (frequencyMap[value] > maxFrequency) // check if the value is max-freq.
			{
				maxFrequency = frequencyMap[value];
				mostFrequentValue = value;
			}
			i = this->keys.nodes[currentKey].info.second.nodes[i].next;// move to the next value
		}
		currentKey = this->keys.nodes[currentKey].next;// move to the next key
	}
	return mostFrequentValue;
}





//N - number of keys
//Best case: Theta(N)
//Worst case: Theta(N)
//Total complexity: Theta(N)
//This function resizes the Dynamic Array (DLLA) by doubling its capacity. 
//It copies the existing elements to the new array, so the time complexity is linear in the number of elements in the DLLA, denoted as N
template<typename TElement>
void MultiMap::resize(DLLA<TElement> &dlla)
{
	dlla.capacity= dlla.capacity * 2;
	DLLANode<TElement> *aux= new DLLANode<TElement>[dlla.capacity];
	for(int i=0; i<dlla.capacity/2;i++)
		aux[i]=dlla.nodes[i];
	for (int i = dlla.capacity / 2; i < dlla.capacity; i++)
	{
		aux[i].next = i + 1;
		aux[i].prev = i - 1;
	}
	aux[dlla.capacity-1].next = -1;// last node
	dlla.firstEmpty= dlla.capacity / 2;
	dlla.nodes=aux;
}

//N - number of keys
//Best case: Theta(1)
//Worst case: Theta(N)
//Total complexity: Theta(N)
// This function adds a value to a DLLA. If the DLLA is full, it calls the resize function, which has a complexity of Theta(N)
template <typename TElement, typename TVal>
void MultiMap::add_to_dlla(DLLA<TElement>& dlla, TVal v)
{
	if (dlla.head == -1)// if the dlla is empty
	{
		dlla.tail = dlla.firstEmpty;// tail is the first empty
		dlla.head = dlla.firstEmpty;// head is the first empty
		dlla.nodes[dlla.head].info = v;// add the value to the first empty

		dlla.firstEmpty = dlla.nodes[dlla.firstEmpty].next;// first empty is the next empty
		dlla.nodes[dlla.head].next = -1;// next of the head is -1
		dlla.size++;
		return;
	}
	if(dlla.size==dlla.capacity)// if the dlla is full
		this->resize(dlla);

	dlla.nodes[dlla.tail].next = dlla.firstEmpty;// next of the tail is the first empty
	dlla.nodes[dlla.firstEmpty].prev = dlla.tail;// prev of the first empty is the tail

	dlla.tail = dlla.firstEmpty;// tail is the first empty
	dlla.firstEmpty= dlla.nodes[dlla.firstEmpty].next;// first empty is the next empty

	dlla.nodes[dlla.tail].info = v;// add the value to the first empty
	dlla.nodes[dlla.tail].next = -1;// next of the tail is -1

	dlla.size++; // increase the size
}


//N - number of keys
//Best case: Theta(1)
//Worst case: Theta(N)
//Total complexity: O(N)
// This function adds a key-value pair to the MultiMap. 
//It first checks if the key already exists by iterating through the keys, which has a complexity of Theta(N).

//When a new key-value pair is added to the MultiMap, it checks if the key already exists. 
//If it does, it adds the new value to the associated DLLA for that key. 
//This allows multiple values to be associated with the same key.
void MultiMap::add(TKey c, TValue v) 
{
	if (!this->isEmpty())// if the multimap is not empty
	{
		int currentKey = this->keys.head;// current key is the head of the keys
		while (currentKey != -1)
		{
			if (this->keys.nodes[currentKey].info.first == c)// if the key already exists
			{
				this->add_to_dlla(this->keys.nodes[currentKey].info.second, v);// add the value to the dlla of the key
				this->number_of_pairs += 1;
				return;
			}
			currentKey = this->keys.nodes[currentKey].next;
		}
	}
	DLLA<TValue> new_key;
	this->add_to_dlla(new_key,v);// add the value to the dlla of the key
	this->add_to_dlla(this->keys, pair<TKey, DLLA<TValue> >(c, new_key));// add the key to the keys
	this->number_of_pairs += 1;
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
//This function deletes an element from a DLLA given its position.
template<typename TElement>
bool MultiMap::delete_dlla(DLLA<TElement>& dlla, int position) 
{
	if (position == dlla.tail) // if the position is the tail
	{
		dlla.tail = dlla.nodes[dlla.tail].prev;
		dlla.nodes[dlla.tail].next = -1;
	}
	else // if the position is not the tail
	{
		if (position == dlla.head) // if the position is the head
		{
			dlla.head = dlla.nodes[position].next;
			dlla.nodes[dlla.head].prev = -1;
		}
		else // if the position is not the head
		{
			int prev_position = dlla.nodes[position].prev;
			int next_position = dlla.nodes[position].next;
			dlla.nodes[prev_position].next = next_position;
			dlla.nodes[next_position].prev = prev_position;
		}
	}

	dlla.nodes[position].prev = -1;
	dlla.nodes[position].next = dlla.firstEmpty;
	dlla.firstEmpty = position;
	dlla.size--;

	if (dlla.size == 0) 
		dlla.head = -1;

	return true;
}


//N is the number of keys and M is the maximum number of values for a key
//Best case: Theta(1)
//Worst case: O(N*M)
//Total complexity: O(N*M)
//This function removes a key-value pair from the MultiMap. 
//It searches for the key by iterating through the keys, which has a complexity of Theta(N). 
//If the key is found, it searches for the value in the associated DLLA, which has a complexity of Theta(M) in the worst case. 
//If the value is found, it calls the delete_dlla function to remove the value from the DLLA
bool MultiMap::remove(TKey c, TValue v) 
{
	if (this->isEmpty()) 
		return false;

	int currentKey = this->keys.head;
	while (currentKey != -1)
	{
		if (this->keys.nodes[currentKey].info.first == c)
		{
			int i= this->keys.nodes[currentKey].info.second.head;// i is the head of the dlla of the key
			while (i != -1)
			{
				if (this->keys.nodes[currentKey].info.second.nodes[i].info == v)// if the value is in the dlla of the key
				{
					this->delete_dlla(this->keys.nodes[currentKey].info.second, i);// delete the value from the dlla of the key
					this->number_of_pairs -= 1;
					if (this->keys.nodes[currentKey].info.second.size == 0) // if the dlla of the key is empty
						this->delete_dlla(this->keys, currentKey);// delete the key from the keys
					return true;
				}
				i = this->keys.nodes[currentKey].info.second.nodes[i].next;
			}
			return false;
		}
		currentKey = this->keys.nodes[currentKey].next;
	}
	return false;
}


//N is the number of keys and M is the maximum number of values for a key
//Best case: Theta(1)
//Worst case: O(N+M)
//Total complexity: O(N+M)
//This function searches for a key in the MultiMap.
//It iterates through the keys, which has a complexity of Theta(N).
//If the key is found, it retrieves the associated values from the DLLA, which has a complexity of Theta(M)
vector<TValue> MultiMap::search(TKey c) const 
{
	if(this->isEmpty())// if the multimap is empty
		return vector<TValue>();

	int currentKey = this->keys.head;
	while (currentKey != -1)// search for the key
	{
		if (this->keys.nodes[currentKey].info.first == c)// if the key exists
		{
			vector <TValue> values;
			int i=this->keys.nodes[currentKey].info.second.head;
			while (i != -1)// add the values from the dlla of the key to the vector
			{
				values.push_back(this->keys.nodes[currentKey].info.second.nodes[i].info);
				i=this->keys.nodes[currentKey].info.second.nodes[i].next;
			}
			return values;// return the vector
		}
		currentKey = this->keys.nodes[currentKey].next;
	}
	return vector<TValue>();
}


// Best case: Theta(1)
// Worst case: Theta(1)
// Total complexity: Theta(1)
int MultiMap::size() const 
{
	return this->number_of_pairs;
}

// Best case: Theta(1)
// Worst case: Theta(1)
// Total complexity: Theta(1)
bool MultiMap::isEmpty() const 
{
	if (this->keys.head == -1) 
		return true;
	return false;
}



//N - number of keys
// Best case: Theta(1)
// Worst case: O(N^2)
// Total complexity: O(N^2)
//This function returns a vector of unique keys in the MultiMap. 
//It iterates through the keys and checks if each key is already in the vector, which has a complexity of O(N^2) in the worst case
vector<TKey> MultiMap::keySet() const
{
	if (this->isEmpty())// if the multimap is empty
		return vector<TKey>();

	vector<TKey> keys;
	int currentKey = this->keys.head;
	while (currentKey != -1)// add the keys to the vector
	{
		bool ok = false;
		for (auto i : keys)// check if the key is already in the vector
		{
			if (i == this->keys.nodes[currentKey].info.first)
			{
				ok = true;
				break;
			}
		}
		if(!ok)
			keys.push_back(this->keys.nodes[currentKey].info.first);

		currentKey = this->keys.nodes[currentKey].next;
	}
	return keys;// return the vector
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
MultiMapIterator MultiMap::iterator() const 
{
	return MultiMapIterator(*this);
}

//This is the destructor for the MultiMap class. 
//It is empty, as the MultiMap does not have any dynamically allocated resources that need to be explicitly deallocated. 
//Therefore, the complexity is Theta(1).
MultiMap::~MultiMap()
{}


