#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	int frcy;
	int current;

public:
	TComp getCurrent();
	
	void next();
	void first();
	bool valid() const;
};

