#define _CRT_SECURE_NO_WARNINGS
#include "repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Repository* createRepository(int capacity)
{// create a new repository
    Repository* Repo = (Repository*)malloc(sizeof(Repository));
    if (Repo == NULL) {
        return NULL;
    }
    Repo->estatesData = createDynamicArray(capacity, (DestroyElementFunction)destroyEstate, (CopyElementFunction)copyEstate);
    return Repo;
}

void destroyEstateRepository(Repository* repository)
{// destroy the repository and deallocate the memory
    if (repository == NULL) {
        return;
    }
    destroyDynamicArray(repository->estatesData);
    free(repository);
    repository = NULL;
}

int getRepoLength(Repository* repository)
{// get the length of the repository and return it
    return repository->estatesData->length;
}

int findEstate(Repository* repository, char address[])
{// find an estate in the repository and return the position of the estate
    int length = getRepoLength(repository);
    for (int i = 0; i < length; i++) {// we go through the repository
        if (strcmp(getAddress((Estate*)repository->estatesData->elements[i]), address) == 0) {
            return i;//if we find the estate, we return the position of the estate
        }
    }
    return -1;
}

int addEstate(Repository* repository, Estate* estate)
{// add an estate to the repository
    int position = findEstate(repository, estate->type);
    if (position == -1) {
        addElement(repository->estatesData, estate);
        return 1;// if the estate was added, we return 1
    }
    else {
        Estate* oldEstate = (Estate*)getElementAtIndex(repository->estatesData, position);
        updateEstate(repository, estate->type, oldEstate->address, estate->price, estate->surface);
        destroyEstate(estate);
        return 1;// if the estate was updated, we return 1
    }
    return 0;// if the estate was not added, we return 0
}
void addTenElements(Repository* repository)// add 10 elements to the repository
{//initial elemets which are the same at each start of the program
    addEstate(repository, createEstate("House", "Oradea", 50, 10067));
    addEstate(repository, createEstate("Apartment", "Satu Mare", 60, 60));
    addEstate(repository, createEstate("Penthouse", "Bucuresti", 40, 80));
    addEstate(repository, createEstate("House", "Bulgaria 10", 70, 90));
    addEstate(repository, createEstate("Apartment", "Marasti AN1", 8, 2));
    addEstate(repository, createEstate("Apartment", "Nufarului 60", 200, 30));
    addEstate(repository, createEstate("House", "Lalelelor 10", 70, 1));
    addEstate(repository, createEstate("Apartment", "DambuRotund 40", 900, 700));
    addEstate(repository, createEstate("Penthouse", "Grigore Alexandrescu", 36, 97));
    addEstate(repository, createEstate("Penthouse", "Apahida nr.50", 365, 25));
}

int deleteEstate(Repository* repository, const char address[])
{// delete an estate from the repo
    int position = findEstate(repository, address);// find the position of the estate
    if (position != -1) {
        deleteElement(repository->estatesData, position);
        return 1;
    }
    else {
        return 0;
    }
}// return 1 for succes and 0 for fail

int updateEstate(Repository* repository, const char* type, const char* address, int price, int surface)
{// update an estate from the repo
    int count = getArrayLength(repository->estatesData);
    for (int i = 0; i < count; i++)
    {// find the estate and update it
        Estate* estate = (Estate*)getElementAtIndex(repository->estatesData, i);
        if (strcmp(getAddress(estate), address) == 0)
        {
            setSurface(estate, surface);
            setPrice(estate, price);
            setType(estate, type);
            return 1;
        }
    }
    return 0;
}// return 1 for succes and 0 for fail

DynamicArray* getRepo(Repository* repository)// return the repo
{
    if (repository == NULL)// if the repo is empty, we return NULL
        return NULL;
    return repository->estatesData;
}

Repository* copyRepo(Repository* repository)// copy the repo
{
    Repository* newRepo = createRepository(repository->estatesData->capacity);
    destroyDynamicArray(newRepo->estatesData);
    newRepo->estatesData = copyDynamicArray(repository->estatesData);
    return newRepo;// return the new repo
}

void testEstateRepo()// tests for the repository
{
    Repository* estateRepo = createRepository(15);
    Estate* estate = createEstate("House", "Oradea", 1230, 856);

    assert(getRepo(estateRepo) == estateRepo->estatesData);


    addEstate(estateRepo, estate);
    Estate* estate2 = createEstate("House", "Oradea", 1230, 856);
    assert(estateRepo->estatesData->elements[0] == estate);
    assert(getRepoLength(estateRepo) == 1);

    updateEstate(estateRepo, "House", "Oradea", 10000, 10000);
    assert(getSurface((Estate*)estateRepo->estatesData->elements[0]) == 10000);
    assert(getPrice((Estate*)estateRepo->estatesData->elements[0]) == 10000);
    estateRepo = NULL;


    destroyEstateRepository(estateRepo);
    assert(estateRepo == NULL);
}
