#include <cstring>
#include <iostream>
#include "repository.h"

Repository::Repository(DynamicArray<Coat>* DArray)// constructor
{
	this->DArray = DArray;
}

int Repository::GetSize()// return the size of the repository
{
	return this->DArray->GetSize();
}

DynamicArray<Coat>* Repository::GetDArray()// return the dynamic array
{
	return this->DArray;
}

Repository::~Repository()// destructor
{
	delete this->DArray;
}

int Repository::AddRepo(string size, string color, int price, int quantity, string photo)
{// add a new coat to the repository
	int poz;
	poz = CheckExistence(size, color, photo);
	if (poz == -1)
	{
		Coat c(size, color, price, quantity, photo);
		this->DArray->Add(c);
		return 0;
	}
	return 1;
}// \param size the size of the coat we are about to add

int Repository::CheckExistence(string size, string color, string photo)
{// check if a coat already exists in the repository
	int i;
	for (i = 0; i < this->DArray->GetSize(); i++)
	{
		if ((*this->DArray)[i].GetSize() == size and (*this->DArray)[i].GetColour() == color and (*this->DArray)[i].GetPhoto() == photo)
			return i;
	}
	return -1;
}// \param size the size of the coat we are about to add

int Repository::DeleteEntireProductRepo(string size, string color, string photo)
{// delete a coat from the repository
	int poz;
	poz = CheckExistence(size, color, photo);
	if (poz == -1)
		return 1;
	this->DArray->Delete(poz);
	return 0;
}// \param size the size of the coat we are about to add

int Repository::DeleteSoldOutRepo(string size, string color, string photo)
{// delete a coat from the repository if it is sold out
	int poz,qua;
	poz = CheckExistence(size, color, photo);
	qua=(*this->DArray)[poz].GetQuantity();
	if (poz != -1 and qua == 0)
	{
		this->DArray->Delete(poz);
		return 0;
	}
	return 1;
}// \param size the size of the coat we are about to add

int Repository::UpdateQuantityRepo(string size, string color, string photo, int quantity)
{// update the quantity of a coat
	int poz;
	poz = CheckExistence(size, color, photo);
	if (poz != -1)
	{
		int pr=(*this->DArray)[poz].GetPrice();
		Coat c(size, color, pr, quantity, photo);
		this->DArray->Update(c, poz);
		return 0;
	}
	return 1;
}// \param size the size of the coat we are about to add

int Repository::UpdatePriceRepo(string size, string color, string photo, int price)
{// update the price of a coat
	int poz;
	poz = CheckExistence(size, color, photo);
	if (poz != -1)
	{
		int qu=(*this->DArray)[poz].GetQuantity();
		Coat c(size, color, price, qu, photo);
		this->DArray->Update(c, poz);
		return 0;
	}
	return 1;
}// \param size the size of the coat we are about to add

/*
void Repository ::init_repo ()
{//add data in the repository
	AddRepo("S", "red", 100, 0, "https://www.google.com/imgres?imgurl");
	AddRepo("XXL", "green", 500, 1, "https://www.youtube.com/watch?v=4U9exgbJ9Q4");
	AddRepo("M", "blue", 200, 0, "https://www.google.com/imgres?imgurl");
	AddRepo("S", "yellow", 100, 0, "https://github.com/cs-ubbcluj-ro/a45-BirouRares");
	AddRepo("L", "orange", 100, 0, "https://www.google.com/imgres?imgurl");
	AddRepo("XL", "blue", 100, 0, "https://www.youtube.com/watch?v=bcaWGXEA0_Y");
	AddRepo("XL", "green", 200, 0, "https://www.olx.ro");
	AddRepo("XL", "white", 100, 0, "https://www.google.com/imgres?imgurl");
	AddRepo("XL", "black", 500, 0, "https://www.google.com/imgres?imgurl");
	AddRepo("XL", "grey", 10000, 1, "https://www.google.com/imgres?imgurl");
}
*/

void Repository ::init_repo ()
{//add data in the repository
	AddRepo("S", "red", 100, 2, "https://www.google.com/imgres?imgurl");
	AddRepo("XXL", "green", 500, 100, "https://www.youtube.com/watch?v=4U9exgbJ9Q4");
	AddRepo("M", "blue", 200, 0, "https://www.google.com/imgres?imgurl");
	AddRepo("S","yellow", 100,100,"https://github.com/cs-ubbcluj-ro/a45-BirouRares");
	AddRepo("L", "orange", 100, 200, "https://www.google.com/imgres?imgurl");
	AddRepo("XL", "blue", 100, 50, "https://www.youtube.com/watch?v=bcaWGXEA0_Y");
	AddRepo("XL", "green", 200, 150, "https://www.olx.ro");
	AddRepo("XL", "white", 100, 520, "https://www.google.com/imgres?imgurl");
	AddRepo("XL", "black", 500, 550, "https://www.google.com/imgres?imgurl");
	AddRepo("XL", "grey", 10000, 5, "https://www.google.com/imgres?imgurl");
} 