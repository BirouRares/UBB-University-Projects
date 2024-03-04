#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b)
{
	this->current = 0;
	this->frcy = bag.elements[this->current].second;
}

// Theta(1)

TComp SortedBagIterator::getCurrent()
{
	if (this->current >= this->bag.nr_pairs)
		throw exception();
	return this->bag.elements[this->current].first;
	//return NULL_TCOMP;
}

// Theta(1)

bool SortedBagIterator::valid() const
{
	if (this->current < this->bag.nr_pairs and this->current >= 0)
		return true;
	return false;
}

// Theta(1)

void SortedBagIterator::next()
{
	if (this->current >= this->bag.nr_pairs)
		throw exception();
	else
	{
		this->frcy--;
		if (this->frcy == 0)
		{
			this->current++;
			if (valid()==true)
				this->frcy = bag.elements[this->current].second;
		}
	}
}

// Theta(1)

void SortedBagIterator::first()
{
	this->current = 0;
	this->frcy = bag.elements[this->current].second;
}

// Theta(1)

