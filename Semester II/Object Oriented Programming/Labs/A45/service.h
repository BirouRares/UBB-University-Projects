#pragma once
#include <cstdlib>
#include <string>
#include "dynamic_array.h"
#include "repository.h"
#include "domain.h"

class Service
{
private:
	Repository* repository;
	Repository* user_repository;
	int total_price;
public:
	~Service();// destructor
	Service(Repository* repository, Repository* user_repository);// constructor
	int AddUserService(Coat c, Coat cUser);// add a coat to the user repository
	int AddService(string size, string color, int price, int quantity, string photo);// add a coat to the repository

	DynamicArray<Coat>* GetRepo();// return the repository
	DynamicArray<Coat>* GetUserRepo();// return the user repository

	int DeleteService(string size, string color, string photo, int crt);// delete a coat from the repository
	int UpdatePriceService(string size, string color, string photo, int price);// update the price of a coat
	int UpdateQuantityService(string size, string color, string photo, int quantity);// update the quantity of a coat
	int GetSize();// return the size of the repository
	int GetTotalPrice() const;// return the total price of the user repository
};