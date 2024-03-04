#pragma once
#include "repository.h"


typedef struct {
	Repository* Repository;
	DynamicArray* undoStack;
	int undoPointer;
} Service;

Service* createService(Repository* Repo);

void destroyService(Service* service);// destroy the service
Repository* getRepository(Service* service);
int add(Service* service, const char* type, const char* address, int surface, int price);// adds a new estate to the repo and return 1 if it was added and 0 if it was not added
int deleteServ(Service* service, const char* address);// deletes an estate from the repo and return 1 if it was deleted and 0 if it was not deleted
int update(Service* service, const char* type, const char* address, int price, int surface);// updates an estate from the repo and return 1 if it was updated and 0 if it was not updated
DynamicArray* getEstates(Service* serv);// get all the estates from the repo
DynamicArray* getEstatesByName(Service* serv, const char* type);// gets the estates with a giving type
DynamicArray* getEstatesBySurface(Service* serv, int surface, const char* type);// gets the estates with a giving surface and type
DynamicArray* getEstatesByPrice(Service* serv, int price);// gets the estates with a giving price
int undo(Service* serv);// undo the last operation and return 1 if it was done and 0 if it was not done
int redo(Service* serv);// redo the last operation and return 1 if it was done and 0 if it was not done

void sortEstatesVectorAscendingByPrice(DynamicArray* arr);// sort the estates by price

void testService();// test the service

