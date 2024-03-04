#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "domain.h"


typedef void* TElem;
typedef void (*DestroyElementFunction)(void*);
typedef TElem(*CopyElementFunction)(TElem);

typedef struct DynamicArray {
	TElem* elements;
	int length;
	int capacity;
	DestroyElementFunction destroyFunction;
	CopyElementFunction copyFunction;
} DynamicArray;

DynamicArray* createDynamicArray(int capacity, DestroyElementFunction destroyFunction, CopyElementFunction copyFunction);

void destroyDynamicArray(DynamicArray* arr); // destroy the array which is dynamic allocated
void addElement(DynamicArray* arr, TElem element); // add an element to the array
void deleteElement(DynamicArray* arr, int position); // delete an element from the array
void* getElementAtIndex(DynamicArray* arr, int index); // get an element from the array
int getArrayLength(DynamicArray* arr);// get the length of the array
TElem* getArrayElements(DynamicArray* arr); // get the elements of the array
DynamicArray* copyDynamicArray(DynamicArray* arr); // copy the array

void testDynamicArray();// test the dynamic array
