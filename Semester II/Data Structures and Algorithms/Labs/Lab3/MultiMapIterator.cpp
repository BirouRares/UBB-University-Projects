#include "MultiMapIterator.h"
#include "MultiMap.h"

//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) 
{
	this->keyIndex = this->col.keys.head;
	this->valueIndex = this->col.keys.nodes[this->keyIndex].info.second.head;
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
TElem MultiMapIterator::getCurrent() const
{
	if(!this->valid())
		throw exception();
	return pair<TKey, TValue>(this->col.keys.nodes[this->keyIndex].info.first, this->col.keys.nodes[this->keyIndex].info.second.nodes[this->valueIndex].info);
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
bool MultiMapIterator::valid() const 
{
	if(this->keyIndex==-1 or this->valueIndex==-1)
		return false;
	return true;
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
void MultiMapIterator::next() {
	if(!this->valid())
		throw exception();
	this->valueIndex=this->col.keys.nodes[this->keyIndex].info.second.nodes[this->valueIndex].next;// move to the next value
	if (this->valueIndex == -1)// if the value is the last one from the dlla of the key
	{
		this->keyIndex=this->col.keys.nodes[this->keyIndex].next;// move to the next key
		this->valueIndex=this->col.keys.nodes[this->keyIndex].info.second.head;// move to the first value from the dlla of the key
	}
}


//Best case: Theta(1)
//Worst case: Theta(1)
//Total complexity: Theta(1)
void MultiMapIterator::first() {
	this->keyIndex=this->col.keys.head;// move to the first key
	this->valueIndex=this->col.keys.nodes[keyIndex].info.second.head;// move to the first value from the dlla of the key
}

