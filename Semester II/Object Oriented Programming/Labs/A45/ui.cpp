#define UNICODE
#define _UNICODE
#include "ui.h"
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

Console::Console()
{}

Console::Console(Service* service, Validator* validator)
{
	this->service = service;
	this->validator = validator;
}

Console::~Console()
{
	delete this->service;
	delete this->validator;
}

void Console::AddAdminConsole()
{
	string size, colour, photo,str_price,str_quantity;
	int price, quantity;
	cout << "Size: ";
	cin >> size;
	cout << "\nColour: ";
	cin >> colour;
	cout << "\nPrice: ";
	cin >> str_price;
	cout << "\nQuantity: ";
	cin >> str_quantity;
	cout << "\nPhoto: ";
	cin >> photo;
	price=this->validator->validate_price_product(str_price);
	quantity=this->validator->validate_quantity_product(str_quantity);
	if (!this->validator->validate_color_product(colour) or !this->validator->validate_size_product(size) or price == -1 or quantity == -1 or !this->validator->validate_photograph_product(photo))
		cout << "\nInvalid data!Try again!\n";
	else
	{
		if(this->service->AddService(size, colour, price, quantity, photo) == 0)
			cout << "\nProduct added successfully!\n";
		else
			cout << "\nProduct already exists!\n";
	}
}

void Console::DisplayProductsAdmin()
{
	for (int i = 0; i < this->service->GetSize(); i++)
		cout<<i+1<<".   Size: " << (*this->service->GetRepo())[i].GetSize() << "   Colour: " << (*this->service->GetRepo())[i].GetColour() << "   Price: " << (*this->service->GetRepo())[i].GetPrice() << "   Quantity: " << (*this->service->GetRepo())[i].GetQuantity() << "   Photo Link: " << (*this->service->GetRepo())[i].GetPhoto() << "\n";
}

void Console::UpdateProductsPriceAdmin()
{
	string size, colour, photo, str_price;
	int price;
	cout << "Size: ";
	cin >> size;
	cout << "\nColour: ";
	cin >> colour;
	cout << "\nPrice: ";
	cin >> str_price;
	cout << "\nPhoto: ";
	cin >> photo;

	price = this->validator->validate_price_product(str_price);
	if (!this->validator->validate_color_product(colour) or !this->validator->validate_size_product(size) or price == -1 or !this->validator->validate_photograph_product(photo))
		cout << "\nInvalid data!Try again!\n";
	else
	{
		if (this->service->UpdatePriceService(size, colour,photo,price) == 0)
			cout << "\nProduct updated successfully!\n";
		else
			cout << "\nProduct doesn't exist!\n";
	}
}

void Console::UpdateProductsQuantityAdmin()
{
	string size, colour, photo, str_quantity;
	int quantity;
	cout << "Size: ";
	cin >> size;
	cout << "\nColour: ";
	cin >> colour;
	cout << "\nQuantity: ";
	cin >> str_quantity;
	cout << "\nPhoto: ";
	cin >> photo;
	quantity = this->validator->validate_quantity_product(str_quantity);
	if (!this->validator->validate_color_product(colour) or !this->validator->validate_size_product(size) or quantity == -1 or !this->validator->validate_photograph_product(photo))
		cout << "\nInvalid data!Try again!\n";
	else
	{
		if (this->service->UpdateQuantityService(size, colour, photo, quantity) == 0)
			cout << "\nProduct updated successfully!\n";
		else
			cout << "\nProduct doesn't exist!\n";
	}
}

void Console::DeleteSoldOutProductAdmin() 
{
	string size, colour, photo;
	cout << "Size: ";
	cin >> size;
	cout << "\nColour: ";
	cin >> colour;
	cout << "\nPhoto: ";
	cin >> photo;
	if (!this->validator->validate_color_product(colour) or !this->validator->validate_size_product(size)  or !this->validator->validate_photograph_product(photo))
		cout << "\nInvalid data!Try again!\n";
	else
	{
		if (this->service->DeleteService(size, colour,photo,2) == 0)
			cout << "\nProduct deleted successfully!\n";
		else
			cout << "\nProduct is not sold out or it does not exists!\n";
	}
}

void Console::DeleteEntireProductAdmin()
{
	string size, colour, photo;
	cout << "Size: ";
	cin >> size;
	cout << "\nColour: ";
	cin >> colour;
	cout << "\nPhoto: ";
	cin >> photo;
	if (!this->validator->validate_color_product(colour) or !this->validator->validate_size_product(size) or !this->validator->validate_photograph_product(photo))
		cout << "\nInvalid data!Try again!\n";
	else
	{
		if (this->service->DeleteService(size, colour, photo, 1) == 0)
			cout << "\nProduct deleted successfully!\n";
		else
			cout << "\nProduct does not exists!\n";
	}
}

void Console::MenuAdminMode()

{
	cout << "\n0. Exit!\n";
	cout << "1. Add a product!\n";
	cout << "2. Display the products!\n";
	cout << "3. Delete a product!\n";
	cout << "4. Delete a sold out product!\n";
	cout << "5. Update the price of a product!\n";
	cout << "6. Update the quantity of a product!\n";
}

void Console::AdminMode()
{
	bool Administrator_Mode = false;
	while (Administrator_Mode == false)
	{
		string opt;
		MenuAdminMode();
		cout << "\nYour option: ";
		cin >> opt;
		if (opt != "1" and opt != "2" and opt != "3" and opt != "4" and opt != "5" and opt != "6" and opt != "7" and opt != "0")
			cout << "\nInvalid command!\n";
		else
		{
			if (opt == "1")
				AddAdminConsole();
			if (opt == "2")
				DisplayProductsAdmin();
			if (opt == "3")
				DeleteEntireProductAdmin();
			if (opt == "4")
				DeleteSoldOutProductAdmin();
			if (opt == "5")
				UpdateProductsPriceAdmin();
			if (opt == "6")
				UpdateProductsQuantityAdmin();
			if (opt == "0")
			{
				cout << "\nYou are out of the administrator mode!\n\n";
				Administrator_Mode = true;
			}
				
		}
	}
}

void Console::start()
{
	bool ok = false;
	while (!ok)
	{
		string opt;
		cout<<"0. Exit!\n";
		cout<<"1. Administrator Mode!\n";
		cout<<"2. User Mode!\n";
		cout<<"\nYour option: ";
		cin >> opt;
		if(opt!="0" and opt!="1" and opt!="2")
			cout<<"\nInvalid command!\n";
		else
		{
			if (opt == "0")
			{
				cout << "\nGoodbye!\n";
				ok = true;
			}	
			if (opt=="1")
				AdminMode();
			if (opt == "2")
				UserMode();
		}

	}
}

void MenuUserMode()
{
	cout << "\n0. Exit!\n";
	cout << "1. Buy products!\n";
	cout<<  "2. Display the shopping basket!\n";
}

int Console::DisplayProductsUser()
{
	int i = 0;
	if (i < this->service->GetSize() and (*this->service->GetRepo())[i].GetQuantity()<=0)
	{
		int ok = 0;
		while ((*this->service->GetRepo())[i].GetQuantity() <= 0 and i < this->service->GetSize())
		{	
			i++;
			if((*this->service->GetRepo())[i].GetQuantity() > 0)
			ok = 1;
		}
		if (ok==0)
			return 1;
		if (i >= this->service->GetSize())
			return 0;
	}
	if (i < this->service->GetSize() and (*this->service->GetRepo())[i].GetQuantity()>0)
	{
		cout << "Size: " << (*this->service->GetRepo())[i].GetSize() << "   Colour: " << (*this->service->GetRepo())[i].GetColour() << "   Price: " << (*this->service->GetRepo())[i].GetPrice() << "   Quantity: " << (*this->service->GetRepo())[i].GetQuantity() << "   Photo Link: " << (*this->service->GetRepo())[i].GetPhoto() << "\n\n";
		ShellExecuteA(NULL, "open", (*this->service->GetRepo())[i].GetPhoto().c_str(), NULL, NULL, SW_SHOWNORMAL);
		cout << "1. Buy\n";
		cout << "2. Next\n";
		cout << "3. Pay\n";
		while (i < this->service->GetSize())
		{
			string opt;
			cout << "\nYour option: ";
			cin >> opt;
			if(opt!= "1" and opt != "2" and opt!="3")
				cout << "\nInvalid command!\n";
			else
			{
				if (opt == "1") 
				{
					if ((*this->service->GetRepo())[i].GetQuantity() > 0)
					{
						this->service->UpdateQuantityService((*this->service->GetRepo())[i].GetSize(), (*this->service->GetRepo())[i].GetColour(), (*this->service->GetRepo())[i].GetPhoto(), (*this->service->GetRepo())[i].GetQuantity() - 1);
						Coat c((*this->service->GetRepo())[i].GetSize(), (*this->service->GetRepo())[i].GetColour(), (*this->service->GetRepo())[i].GetPrice(), 1, (*this->service->GetRepo())[i].GetPhoto());
						if (this->service->AddUserService((*this->service->GetRepo())[i], c) == 1)
							continue;
						DisplayTotalPrice();

						i++;
						if (i < this->service->GetSize() and (*this->service->GetRepo())[i].GetQuantity()>0)
						{
							cout << "\nSize: " << (*this->service->GetRepo())[i].GetSize() << "   Colour: " << (*this->service->GetRepo())[i].GetColour() << "   Price: " << (*this->service->GetRepo())[i].GetPrice() << "   Quantity: " << (*this->service->GetRepo())[i].GetQuantity() << "   Photo Link: " << (*this->service->GetRepo())[i].GetPhoto() << "\n";
							ShellExecuteA(NULL, "open", (*this->service->GetRepo())[i].GetPhoto().c_str(), NULL, NULL, SW_SHOWNORMAL);
							cout << "1. Buy\n";
							cout << "2. Next\n";
							cout << "3. Pay\n";
						}
						else
						{
							if (i >= this->service->GetSize())
								return 0;
							while ((*this->service->GetRepo())[i].GetQuantity() <= 0 and i < this->service->GetSize())
								i++;

							if (i >= this->service->GetSize())
								return 0;

							cout << "\nSize: " << (*this->service->GetRepo())[i].GetSize() << "   Colour: " << (*this->service->GetRepo())[i].GetColour() << "   Price: " << (*this->service->GetRepo())[i].GetPrice() << "   Quantity: " << (*this->service->GetRepo())[i].GetQuantity() << "   Photo Link: " << (*this->service->GetRepo())[i].GetPhoto() << "\n";
							ShellExecuteA(NULL, "open", (*this->service->GetRepo())[i].GetPhoto().c_str(), NULL, NULL, SW_SHOWNORMAL);
							cout << "1. Buy\n";
							cout << "2. Next\n";
							cout << "3. Pay\n";
						}
					}
					else
					{
						if (i >= this->service->GetSize())
							return 0;
						while ((*this->service->GetRepo())[i].GetQuantity() <= 0 and i < this->service->GetSize())
							i++;

						if (i >= this->service->GetSize())
							return 0;
					}
				}
				if (opt == "2")
				{
					i++;
					if (i < this->service->GetSize() and (*this->service->GetRepo())[i].GetQuantity()>0)
					{
						cout << "\nSize: " << (*this->service->GetRepo())[i].GetSize() << "   Colour: " << (*this->service->GetRepo())[i].GetColour() << "   Price: " << (*this->service->GetRepo())[i].GetPrice() << "   Quantity: " << (*this->service->GetRepo())[i].GetQuantity() << "   Photo Link: " << (*this->service->GetRepo())[i].GetPhoto() << "\n";
						ShellExecuteA(NULL, "open", (*this->service->GetRepo())[i].GetPhoto().c_str(), NULL, NULL, SW_SHOWNORMAL);
						cout << "1. Buy\n";
						cout << "2. Next\n";
						cout << "3. Pay\n";
					}
					else
					{
						if (i >= this->service->GetSize())
							return 0;
						while ((*this->service->GetRepo())[i].GetQuantity() <= 0 and i < this->service->GetSize())
							i++;

						if (i >= this->service->GetSize())
							return 0;

						cout << "\nSize: " << (*this->service->GetRepo())[i].GetSize() << "   Colour: " << (*this->service->GetRepo())[i].GetColour() << "   Price: " << (*this->service->GetRepo())[i].GetPrice() << "   Quantity: " << (*this->service->GetRepo())[i].GetQuantity() << "   Photo Link: " << (*this->service->GetRepo())[i].GetPhoto() << "\n";
						ShellExecuteA(NULL, "open", (*this->service->GetRepo())[i].GetPhoto().c_str(), NULL, NULL, SW_SHOWNORMAL);
						cout << "1. Buy\n";
						cout << "2. Next\n";
						cout << "3. Pay\n";
					}
						
				}
				if (opt == "3")
					return -1;
			}	
		}
	}
	return 1;
}

void Console::MenuDisplayProductsUser()
{
	int d = 0;
	if (this->service->GetSize() == 0)
		cout << "There are no products on stock!";
	else
	{
		while (d == 0)
			d = DisplayProductsUser();
	}
	if(d==1)
		cout << "\nThere are no products avalible!\n";
}

void Console::DisplayShoppingBag()
{
	for(int i=0;i< this->service->GetUserRepo()->GetSize();i++)
		cout << i+1 << ". Size: " << (*this->service->GetUserRepo())[i].GetSize() << "   Colour: " << (*this->service->GetUserRepo())[i].GetColour() << "   Price: " << (*this->service->GetUserRepo())[i].GetPrice() << "   Quantity: " << (*this->service->GetUserRepo())[i].GetQuantity() << "   Photo Link: " << (*this->service->GetUserRepo())[i].GetPhoto() << "\n\n";
	cout<<"\nThe total sum: "<<this->service->GetTotalPrice()<<"\n";
}

void Console::DisplayTotalPrice()
{
	cout << "\nThe total sum: " << this->service->GetTotalPrice() << "\n";
}

void Console::UserMode()
{
	bool ok = false;
	while (!ok)
	{
		MenuUserMode();
		string opt;
		cout << "\nYour option: ";
		cin >> opt;
		if (opt != "0" and opt != "1" and opt != "2")
			cout << "\nInvalid command!\n";
		else
		{
			if (opt == "1")
				MenuDisplayProductsUser();
			if (opt == "2")
				DisplayShoppingBag();
			if (opt == "0")
			{
				cout << "\nYou are out of the user mode!\n\n";
				ok = true;
			}
		}
	}
}