#define _CRT_SECURE_NO_WARNINGS
#include "service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

Service* createService(Repository* Repo)//create the service
{
    Service* service = (Service*)malloc(sizeof(Service));
    if (service == NULL) {
        return NULL;
    }
    service->Repository = Repo;
    addTenElements(service->Repository);
    service->undoStack = createDynamicArray(10, (DestroyElementFunction)destroyEstateRepository, (CopyElementFunction)copyRepo);
    addElement(service->undoStack, copyRepo(service->Repository));
    service->undoPointer = -1;
    return service;
}

void destroyService(Service* service)//destroy the service allocated
{
    if (service == NULL) {
        return;
    }
    destroyEstateRepository(service->Repository);
    destroyDynamicArray(service->undoStack);
    free(service);
    service = NULL;
}

Repository* getRepository(Service* service)// get the repository
{
    return service->Repository;// returns the repository
}

void correctUndoPointer(Service* serv)// manages the undo pointer
{
    while (getArrayLength(serv->undoStack) - 2 != serv->undoPointer)// while the undo pointer is not at the end of the stack
        deleteElement(serv->undoStack, getArrayLength(serv->undoStack) - 1);// we delete the last element
}

void addToUndoList(Service* serv)
{
    correctUndoPointer(serv);// we correct the undo pointer
    addElement(serv->undoStack, copyRepo(serv->Repository));// we add the repository to the undo stack
    serv->undoPointer++;// we increment the undo pointer when adding to the undo stack
}

int add(Service* service, const char* type, const char* address, int surface, int price)
{
    Estate* estate = createEstate(type, address, surface, price);
    int returnValue = addEstate(service->Repository, estate);// add the estate to the repository
    if (returnValue == 1)
        addToUndoList(service);// also add to undo 
    return returnValue;// returns 1 if the estate was added, 0 otherwise
}

int deleteServ(Service* service, const char* address)// delete an estate from the repository
{
    int returnValue = deleteEstate(service->Repository, address);
    if (returnValue == 1)
        addToUndoList(service);// also add to undo lsit
    return returnValue;// returns 1 if the estate was deleted, 0 otherwise
}

int update(Service* service, const char* type, const char* address, int price, int surface)
{
    int returnValue = updateEstate(service->Repository, type, address, price, surface);
    if (returnValue == 1)
        addToUndoList(service);// also add the new operation to the undo list
    return returnValue;// returns 1 if the estate was updated, 0 otherwise
}

DynamicArray* getEstates(Service* serv)
{
    if (serv == NULL)
        return NULL;
    return getRepo(serv->Repository);
}

void sortEstatesVectorAscendingByPrice(DynamicArray* v)// this function sort the given array
{
    if (v == NULL)
        return;
    int go=0;
    do {
        go = 1;
        for (int i = 1; i < v->length; i++)// we are using the sort to put the elements in order
        {
            if (getPrice((Estate*)v->elements[i]) < getPrice((Estate*)v->elements[i - 1]))
            {
                go = 0;
                void* tmp = v->elements[i];
                v->elements[i] = v->elements[i - 1];
                v->elements[i - 1] = tmp;
            }
        }
    } while (!go);
}// this function does not return anything



int undo(Service* serv)// undo service
{// this function return 1 if the operation was done, 0 otherwise
    int undoStackLength = getArrayLength(serv->undoStack);
    if (undoStackLength <= 1 || serv->undoPointer < 0)
        return 0;
    else
    {
        destroyEstateRepository(serv->Repository);// destroy the repo containing the current data
        serv->Repository = copyRepo((Repository*)getElementAtIndex(serv->undoStack, serv->undoPointer));
        serv->undoPointer--;
        return 1;
    }
}

int redo(Service* serv)// redo service
{// this function return 1 if the operation was done, 0 otherwise
    int undoStackLength = getArrayLength(serv->undoStack);
    if (serv->undoPointer == undoStackLength - 2 || serv->undoPointer < -1)
        return 0;
    else
    {
        destroyEstateRepository(serv->Repository);
        serv->Repository = copyRepo((Repository*)getElementAtIndex(serv->undoStack, serv->undoPointer + 2));
        serv->undoPointer++;
        return 1;
    }
}

DynamicArray* getEstatesByName(Service* serv, const char* type)
{// this function return the estates with the given type
    if (serv == NULL || type == NULL)
        return NULL;
    DynamicArray* meds = getEstates(serv);
    DynamicArray* result = createDynamicArray(meds->capacity, (DestroyElementFunction)destroyEstate, (CopyElementFunction)copyEstate);

    int count = getArrayLength(meds);
    for (int i = 0; i < count; i++)
    {
        Estate* estate = (Estate*)getElementAtIndex(meds, i);
        if (strstr(getAddress(estate), type))
        {
            Estate* copyEstate = createEstate(getType(estate), getAddress(estate), getSurface(estate), getPrice(estate));
            addElement(result, copyEstate);
        }
    }
    return result;
}

DynamicArray* getEstatesBySurface(Service* serv, int surface, const char* type)
{// this function returns the estates with the given surface and type
    if (serv == NULL || surface < 0) 
        return NULL;

    DynamicArray* estates = getEstates(serv);
    DynamicArray* result = createDynamicArray(estates->capacity, (DestroyElementFunction)destroyEstate, (CopyElementFunction)copyEstate);
    int count = getArrayLength(estates);
    for (int i = 0; i < count; i++)// search for the given type
    {
        Estate* estate = (Estate*)getElementAtIndex(estates, i);
        const char* new_type[50];
        strcpy(new_type, estate->type);
        int new_surf = estate->surface;
        if (new_surf >= surface) {
            if (strcmp(new_type, type) == 0) {
                Estate* copyEstate = createEstate(getType(estate), getAddress(estate), getSurface(estate), getPrice(estate));
                addElement(result, copyEstate);
            }
        }
    }
    return result;
}



void testService()// test the functionalities 
{
    Repository* Repo = createRepository(15);
    Service* serv = createService(Repo);

    add(serv, "abcd", "mer", 10, 8);
    assert(getRepoLength(serv->Repository) == 11);

    update(serv, "abcd", "mer", 100, 100);
    assert(getSurface((Estate*)serv->Repository->estatesData->elements[10]) == 100);
    assert(getPrice((Estate*)Repo->estatesData->elements[10]) == 100);


    undo(serv);
    assert(serv->Repository->estatesData->length == 11);

    redo(serv);
    assert(serv->Repository->estatesData->length == 11);

    deleteServ(serv, "mer");
    assert(serv->Repository->estatesData->length == 10);

    serv = NULL;

    destroyService(serv);
    assert(serv == NULL);
}
