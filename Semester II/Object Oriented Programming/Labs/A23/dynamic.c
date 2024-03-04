#define _CRT_SECURE_NO_WARNINGS
#include "dynamic.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity, DestroyElementFunction destroyFunction, CopyElementFunction copyFunction)
{// here we create a dynamic vay
    DynamicArray* v = (DynamicArray*)malloc(sizeof(DynamicArray));// we allocate memory for the vay
    if (v == NULL) {
        return NULL;
    }// if the array is null we return null
    v->capacity = capacity;
    v->length = 0;
    v->elements = (TElem*)malloc(sizeof(TElem) * capacity);
    if (v->elements == NULL) {
        return NULL;
    }
    v->destroyFunction = destroyFunction;
    v->copyFunction = copyFunction;

    return v;// we return the array
}

void destroyDynamicArray(DynamicArray* v)// we destroy the array
{
    if (v == NULL) {
        return;
    }
    for (int i = 0; i < v->length; i++) {
        v->destroyFunction(v->elements[i]);
    }
    free(v->elements);
    v->elements = NULL;

    free(v);// we free the memory
    v = NULL;
}

void resize(DynamicArray* v)
{// this function does not return anything but, it reallocates the memory for the dyanmic array
    if (v == NULL) 
        return;

    v->capacity *= 2;
    void** auxArr = (void**)realloc(v->elements, sizeof(void*) * v->capacity);
    if (auxArr == NULL) 
        return;
    v->elements = auxArr;
}

void addElement(DynamicArray* v, TElem element)
{// add a new elemet to the dyanmic array
    // the function does not return anything
    if (v == NULL) 
        return;
    if (v->elements == NULL) 
        return;
    if (v->length == v->capacity) 
        resize(v);

    v->elements[v->length] = element;
    v->length++;
}

void deleteElement(DynamicArray* v, int position)
{// delete an element from the dynamic array
    //does not return anything
    if (v == NULL) 
        return;
    if (v->elements == NULL) 
        return;
    if (position < 0 || position >= v->length) 
        return;
    
    v->destroyFunction(v->elements[position]);
    for (int i = position; i < v->length - 1; i++) {
        v->elements[i] = *(v->elements + i + 1);
    }
    v->length--;
}

void* getElementAtIndex(DynamicArray* v, int index)
{// get an element with a specific index from the dynamic array
    if (v == NULL)
        return NULL;
    int count = getArrayLength(v);
    if (index < 0 || index >= count)
        return NULL;
    return v->elements[index];// return the elemts
}

int getArrayLength(DynamicArray* v)
{// returns the lenght of the array
    if (v == NULL)
        return -1;

    return v->length;
}

TElem* getArrayElements(DynamicArray* v)
{
    if (v == NULL)
        return NULL;
    if (v->elements == NULL)
        return NULL;
    return v->elements;// get all the elemets from the dynamic array
}

DynamicArray* copyDynamicArray(DynamicArray* v)
{
    DynamicArray* newArr = createDynamicArray(v->capacity, v->destroyFunction, v->copyFunction);
    for (int i = 0; i < v->length; i++)
    {
        addElement(newArr, v->copyFunction(getElementAtIndex(v, i)));
    }
    return newArr;// creates a copy for the dynamic array, used for the undo/redo
}

void testDynamicArray()// test
{
    Estate* estate = createEstate("House", "Oradea", 312, 100);
    DynamicArray* v = createDynamicArray(10, (DestroyElementFunction)destroyEstate, (CopyElementFunction)copyEstate);
    addElement(v, estate);
    assert(v->length == 1);

    assert(getArrayLength(v) == 1);

    Estate* estate1 = (Estate*)getElementAtIndex(v, 0);
    assert(estate->address == estate1->address);

    destroyDynamicArray(v);

}

