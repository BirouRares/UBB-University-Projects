#pragma once
#include "domain.h"
#include "dynamic.h"
#include <stdlib.h>

typedef struct {
	DynamicArray* estatesData;
} Repository;
Repository* createRepository(int capacity);// we create a repository
void destroyEstateRepository(Repository* repository);
int getRepoLength(Repository* repository);// get the number of elements in the repo
int findEstate(Repository* repository, char typename[], char address[], int price); // find an estate in the repo
int addEstate(Repository* repository, Estate* estate);// add an estate to the repo
void addTenElements(Repository* repository);  // add 10 for the beginning elements to the repo
int deleteEstate(Repository* repository, const char* address); // delete an estate from the repo
int updateEstate(Repository* repository, const char* type, const char* address, int price, int Surface);// update an estate from the repo
DynamicArray* getRepo(Repository* repository);// get the repo

Repository* copyRepo(Repository* repository);

void testEstateRepo();
