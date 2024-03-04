#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->capacity = 100;
	this->nr_pairs = 0;
	this->relation = r;
	this->elements = new std::pair<TComp, int>[this->capacity];
}

void SortedBag::addAll(const SortedBag& b)
{
	SortedBagIterator it = b.iterator();
	while (it.valid())
	{
		TElem elem = it.getCurrent();
		this->add(elem);
		it.next();
	}
}
// Best case: Theta(n) 
// Worst case: Theta(n*m)
// Total complexity: O(n)




void SortedBag::resize()
{
	std::pair<TComp, int>* new_elements = new std::pair<TComp, int>[this->capacity * 2];
	this->capacity = this->capacity * 2;
	for (int i = 0; i < this->nr_pairs; i++)
	{
		new_elements[i].first = this->elements[i].first;
		new_elements[i].second = this->elements[i].second;
	}
	delete[] this->elements;
	this->elements = new_elements;
}

// Total complexity: O(nr_pairs)

void SortedBag::add(TComp e) 
{
	int i = 0, poz = 0;
	bool same = false, found = false, first = false, final = false;

	if (this->nr_pairs >= capacity)// if we need to do a resize
		resize();

	if (this->nr_pairs == 0)// In this case, it means we have no elements so we place the fist one on position 0
	{
		elements[this->nr_pairs].first = e;
		elements[this->nr_pairs].second = 1;
		this->nr_pairs++;
		first = true;
	}

	while (i < this->nr_pairs && !found && !first)/// check whether the element already exists
	{
		if (this->elements[i].first == e and !same)
		{
			this->elements[i].second++;
			found = true;
			same = true;
		}
		else
		{
			if (relation(e, this->elements[i].first) and !same)// If it doesn't then we check the relation
			{// If the relation is true, we place the element on the position i
				found = true;
				poz = i;
			}
		}
		i++;
	}

	i = this->nr_pairs;

	while (i > poz and !same and !first and found)// In case the element doesn't exist
	{// shift all the elements to the right once in order to make place for the element which will be inserted.
		this->elements[i].first = this->elements[i - 1].first;
		this->elements[i].second = this->elements[i - 1].second;
		i--;
		final = true;
	}

	if (final == true)
	{
		nr_pairs++;
		this->elements[poz].first = e;
		this->elements[poz].second = 1;
		//this->nr_pairs++;
	}

	if (!same and !found and !final and !first)
	{// If we reached this place it means that the element should be placed on the last position of the array
		this->elements[nr_pairs].first = e;
		this->elements[nr_pairs].second = 1;
		nr_pairs++;
	}
}
// Worst case: Theta(nr_pairs)

// Best case: Theta(1)

// Total Complexity : O(nr_pairs)


bool SortedBag::remove(TComp e)
{
	bool found = false, occ = false;
	int i = 0, poz = 0;

	while (i < this->nr_pairs and !found and !occ)// We search for the element and we check if it has more than one occurence
	{
		if (elements[i].first == e)
		{
			elements[i].second--;
			found = true;
			poz = i;
			//if (elements[i].second >1)
			//	occ = true;
		}
		if (elements[i].second == 0)
		{
			occ = true;
			this->nr_pairs--;
		}
		i++;
	}
	i = poz;
	while (found and occ and i < this->nr_pairs)
	{
		this->elements[i].first = this->elements[i + 1].first;
		this->elements[i].second = this->elements[i + 1].second;
		i++;
	}
	if (found == true)
		return true;
	return false;
}
// Worst case: Theta(nr_pairs)

// Best case: Theta(1)

// Total Complexity : O(nr_pairs)

bool SortedBag::search(TComp elem) const
{
	int i = 0;
	bool found = false;
	while (i < this->nr_pairs and found == false)
	{
		if (this->elements[i].first == elem)
			found = true;
		i++;
	}
	if (found)
		return true;
	return false;
}
// Worst case: Theta(nr_pairs)

// Best case: Theta(1)

// Total Complexity : O(nr_pairs)

int SortedBag::nrOccurrences(TComp elem) const
{
	int i = 0;
	bool found = false;
	while (i < this->nr_pairs and !found)
	{
		if (this->elements[i].first == elem)
			found = true;
		i++;
	}
	if (found)
		return this->elements[i - 1].second;
	return 0;
}
// Worst case: Theta(nr_pairs)

// Best case: Theta(1)

// Total Complexity : O(nr_pairs)


int SortedBag::size() const
{
	int i = 0, n = 0;
	while (i < this->nr_pairs)
	{
		n += this->elements[i].second ;
		i++;
	}
	//return 0;
	return n;
}

// Worst case: Theta(nr_pairs)

// Best case: Theta(1)

// Total Complexity : O(nr_pairs)


bool SortedBag::isEmpty() const
{
	if (this->nr_pairs != 0)
		return false;
	return true;
}

// Worst case: Theta(1)


SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}

// Worst case: Theta(1)

SortedBag::~SortedBag()
{
	delete[] this->elements;
}	

/// Worst case: Theta(1)


///Total Complexity : Theta(nr_pairs)
