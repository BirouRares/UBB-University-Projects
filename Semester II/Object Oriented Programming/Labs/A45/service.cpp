#include "service.h"
#include <cstring>
#include <iostream>

Service::Service(Repository* repository, Repository* user_repository)// constructor
{
	this->repository = repository;
	this->user_repository = user_repository;
	this->total_price = 0;
}// \param repository the repository we are about to add

Service::~Service()// destructor
{
	delete this->repository;
	delete this->user_repository;
}// \param repository the repository we are about to add

int Service::AddService(string size, string color, int price, int quantity, string photo)
{// add a coat to the repository
	if(this->repository->AddRepo(size, color, price, quantity, photo) == 0)
		return 0;
	return 1;
}// \param size the size of the coat we are about to add

DynamicArray<Coat>* Service::GetRepo()
{// return the repository
	return this->repository->GetDArray();
}

DynamicArray<Coat>* Service::GetUserRepo()
{// return the user repository
	return this->user_repository->GetDArray();
}

int Service::GetSize()
{// return the size of the repository
	return this->GetRepo()->GetSize();
}

int Service::AddUserService(Coat c, Coat cUser)
{// add a coat to the user repository
	int poz=this->user_repository->CheckExistence(cUser.GetSize(), cUser.GetColour(), cUser.GetPhoto());
	if (poz == -1)
	{// if the coat does not exist in the user repository
		this->user_repository->AddRepo(cUser.GetSize(), cUser.GetColour(), cUser.GetPrice(), cUser.GetQuantity(), cUser.GetPhoto());
		this->total_price += cUser.GetPrice();
	}
	else
	{// if the coat already exists in the user repository
		int new_quantity=(*this->user_repository->GetDArray())[poz].GetQuantity() + 1;
		this->user_repository->UpdateQuantityRepo(cUser.GetSize(), cUser.GetColour(), cUser.GetPhoto(), new_quantity);
		this->total_price += cUser.GetPrice();
	}
	/*if (c.GetQuantity() == 0)
	{// if the coat is sold out
		this->repository->DeleteEntireProductRepo(c.GetSize(), c.GetColour(), c.GetPhoto());
		return 1;
	}*/
	return 0;
}// \param size the size of the coat we are about to add

int Service::DeleteService(string size, string color, string photo, int crt)
{// delete a coat from the repository
	if (crt == 1)
	{
		if(this->repository->DeleteEntireProductRepo(size, color, photo) == 0)// delete the entire product
			return 0;
		return 1;
	}
	else
	if(crt==2)
	{
		if(this->repository->DeleteSoldOutRepo(size, color, photo) == 0)// delete the sold out products
			return 0;
		return 1;
	}
	return 1;
}// \param size the size of the coat we are about to add

int Service::UpdatePriceService(string size, string color, string photo, int price)
{// update the price of a coat
	if(this->repository->UpdatePriceRepo(size, color, photo, price) == 0)
		return 0;
	return 1;
}// \param size the size of the coat we are about to add

int Service::UpdateQuantityService(string size, string color, string photo, int quantity)
{// update the quantity of a coat
	if(this->repository->UpdateQuantityRepo(size, color, photo, quantity) == 0)
		return 0;
	return 1;
}// \param size the size of the coat we are about to add

int Service::GetTotalPrice() const
{// return the total price of the user repository
	return this->total_price;
}