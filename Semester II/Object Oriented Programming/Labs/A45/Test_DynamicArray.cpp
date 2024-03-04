#include "Test_DynamicArray.h"
#include "dynamic_array.h"
#include <assert.h>
#include <iostream>

void Test_DynamicArray::TestAllDynamicArray()
{
	TestClear();
	TestAdd();
	TestDelete();
	TestUpdate();
	TestGetSize();
	TestResize();
}

void Test_DynamicArray::TestClear()
{
	DynamicArray<int>* d = new DynamicArray<int>(2);
	d->Add(1);
	d->Add(2);
	d->Add(2);
	assert(d->GetSize() == 3);
	d->Delete(0);
	assert(d->GetSize() == 2);
	d->Delete(0);
	assert(d->GetSize() == 1);
	d->Delete(0);
	assert(d->GetSize() == 0);
	delete d;

}
void Test_DynamicArray::TestAdd()
{
	DynamicArray<int>* DA = new DynamicArray<int>(2);
	DA->Add(1);
	assert((*DA)[0] == 1);
	DA->Add(2);
	assert((*DA)[1] == 2);
	delete DA;
}
void Test_DynamicArray::TestResize()
{
	DynamicArray<int>* d= new DynamicArray<int>(2);
	d->Add(1);
	d->Add(2);
	d->Add(3);
	assert(d->GetSize() == 3);
	delete d;
}
void Test_DynamicArray::TestDelete()
{
	DynamicArray<int>* d = new DynamicArray<int>(2);
	d->Add(1);
	d->Add(2);
	d->Add(3);
	assert(d->GetSize() == 3);
	d->Delete(0);
	assert(d->GetSize() == 2);
	d->Delete(0);
	assert(d->GetSize() == 1);
	d->Delete(0);
	assert(d->GetSize() == 0);
	delete d;
}

void Test_DynamicArray::TestUpdate()
{
	DynamicArray<int>* d = new DynamicArray<int>(2);
	d->Add(1);
	d->Add(2);
	d->Add(3);
	d->Update(4, 1);
	assert((*d)[1] == 4);
	delete d;
}
void Test_DynamicArray::TestGetSize()
{
	DynamicArray<int>* d = new DynamicArray<int>(2);
	d->Add(1);
	d->Add(2);
	d->Add(3);
	assert(d->GetSize() == 3);
	d->Delete(1);
	assert(d->GetSize() == 2);
	d->Delete(0);
	assert(d->GetSize() == 1);
	d->Delete(0);
	assert(d->GetSize() == 0);
	delete d;
}