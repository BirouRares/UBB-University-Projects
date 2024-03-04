#pragma once
#include <cstdlib>
#include "domain.h"
#include "dynamic_array.h"
#include <string>

class Repository
{
private:
	DynamicArray<Coat>* DArray;
public:
	~Repository();// destructor
	void init_repo();// initialize the repository
	void print_repo();// print the repository
	int GetSize();// return the size of the repository
	DynamicArray<Coat>* GetDArray();// return the dynamic array
	Repository (DynamicArray<Coat>* DArray);// constructor
	int AddRepo(string size, string color, int price, int quantity, string photo);// add a new coat to the repository
	int CheckExistence(string size, string color, string photo);// check if a coat already exists in the repository
	int DeleteEntireProductRepo(string size, string color, string photo);// delete a coat from the repository
	int DeleteSoldOutRepo(string size, string color, string photo);// delete a coat from the repository if it is sold out
	int UpdatePriceRepo(string size, string color, string photo, int price);// update the price of a coat
	int UpdateQuantityRepo(string size, string color, string photo, int quantity);// update the quantity of a coat

	Coat& operator [] (int poz) {// return the coat from the position poz
		return (*this->DArray)[poz];
	}
};
