#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	template <typename TElement>
	struct DLLANode {
		TElement info;
		int prev;
		int next;
	};

	template<typename TElement>
	struct DLLA {
		DLLANode<TElement> *nodes;
		int head;
		int tail;
		int capacity;
		int firstEmpty;
		int size;

		DLLA()
		{
			capacity = 2;// initial capacity
			size = 0;// initial size
			head = -1;// initial head
			tail = -1;// initial tail
			firstEmpty = 0;// initial first empty
			nodes = new DLLANode<TElement>[capacity];// initial nodes
			for (int i = 0; i < capacity - 1; i++)// initial links
			{
				nodes[i].next = i + 1;
				nodes[i].prev = i-1;
			}
			nodes[capacity - 1].next = -1;// last node
			nodes[capacity - 1].prev = capacity - 2;
		}

		~DLLA()
		{
			if (nodes == nullptr)
				return;
			nodes= nullptr;
		}
	};

	DLLA <pair<TKey, DLLA<TValue>>> keys;
	int number_of_pairs;

public:
	//constructor
	MultiMap();

	template<typename TElement>
	void resize(DLLA<TElement>& dlla);// resizes the dlla


	template<typename TElement, typename TVal>
	void add_to_dlla(DLLA<TElement>& dlla, TVal v);// adds a value to the dlla


	template<typename TElement>
	bool delete_dlla(DLLA<TElement>& dlla, int position);// deletes a value from the dlla

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns a vector with all the keys from the MultiMap
	vector<TKey> keySet() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;


	//returns the TValue that appears most frequently in the MultiMap.
	//if multiple TValues apear most frequently, returns any of them
	//if the MultiMap is empty, the operation returns NULL_TVALUE
	TValue mostFrequent() const;

	//descturctor
	~MultiMap();


};

