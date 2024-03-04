#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	int current_position;
	int copy_current_position;
	struct Node* current;
	TComp* copy_elements;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

