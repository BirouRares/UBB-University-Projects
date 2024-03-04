#include "UI.h"
#include "errors.h"
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

void UI::handleAdd()
{
	string size, colour, photo;
	int price, quantity;
	cout << "Size: ";
	std::cin >> size;
	cout << "\nColour: ";
	std::cin >> colour;
	cout << "\nPrice: ";
	std::cin >> price;
	if (std::cin.fail())
	{
		std::cout << "\nInvalid input!\n\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return;
	}
	cout << "\nQuantity: ";
	std::cin >> quantity;
	if (std::cin.fail() or quantity < 0)
	{
		std::cout << "\nInvalid input!\n\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return;
	}
	cout << "\nPhoto: ";
	std::cin >> photo;
	std::cout << "\n";
	int ok = 0;
	try
	{
		this->adminService.addCoatServ(size, colour, price, quantity, photo);
	}
	catch (RepoError e)
	{
		ok = 1;
		std::cout << e.what() << "\n\n";
	}
	if(ok==0)
	{
		std::cout << "Process terminated!\n\n";
	}
}

void UI::handleRemove()
{
	std::string size, color, photo;
	std::cout << "Size: ";
	std::cin >> size;
	std::cout << "\nColour: ";
	std::cin >> color;
	std::cout << "\nPhoto: ";
	cin >> photo;
	std::cout << "\n";
	try
	{
		this->adminService.removeCoatServ(size, color, photo);
		std::cout << "Coat removed successfully!\n\n";
	}
	catch (RepoError e)
	{
		std::cout << e.what() << "\n\n";
	}
}

void UI::handleUpdate()
{
	std::string size, colour, photo;
	int price, quantity;
	std::cout << "Size: ";
	std::cin >> size;
	std::cout << "\nColour: ";
	std::cin >> colour;
	std::cout << "\nPrice: ";
	std::cin >> price;
	if (std::cin.fail() or price < 0)
	{
		std::cout << "Invalid input!\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return;
	}
	std::cout << "\nQuantity: ";
	std::cin >> quantity;
	if (std::cin.fail() or price < 0)
	{
		std::cout << "Invalid input!\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return;
	}
	std::cout << "\nPhoto: ";
	std::cin >> photo;
	std::cout << "\n";
	
	try
	{
		this->adminService.updateCoatServ( size, colour, price, quantity,photo);
		std::cout << "Coat updated successfully!\n\n";
	}
	catch (RepoError e)
	{
		std::cout << e.what() << "\n\n";
	}
}

void UI::printCoat()
{
	std::vector<Coat> arr= this->adminService.getCoatList();
	if(arr.size()==0)
		std::cout << "No coats!\n\n";
	for (auto i : arr)
	{
		std::cout << i << "\n";
	}
	std::cout << "\n";
}

void UI::printShoppingBag()
{
	std::vector<Coat> arr = this->userService.getCoatList();
	for (auto i : arr)
	{
		std::cout << i << "\n";
	}
	std::cout << "\n";
	std::cout<<"Total price: " << this->userService.TotalPrice() << "\n\n";
}

void UI::openFile()
{
	std::string command = std::string("start ").append(this->userService.getFileName());
	system(command.c_str());
}

void UI::displayAdminMenu()
{
	std::cout << "1. Add coat\n";
	std::cout << "2. Remove coat\n";
	std::cout << "3. Update coat\n";
	std::cout << "4. Display coats\n";
	std::cout << "5. Exit\n\n";
	std::cout << "Your option: ";
}

void UI::displayUserMenu()
{
	std::cout << "1. Buy products\n";
	std::cout << "2. Display shopping bag\n";
	std::cout << "3. Open file\n";
	std::cout << "4. Exit\n\n";
	std::cout << "Your option: ";
}

UI::UI(Service& adminService, UserService& userService) : adminService{ adminService }, userService{ userService }
{}

void UI::run()
{
	std::string opt;
	int userFile = 0;
	while (true)
	{
		
		std::cout << "1. Administrator Mode!\n";
		std::cout << "2. User Mode!\n";
		std::cout << "3. Exit!\n";
		std::cout << "\nYour option: ";
		std::cin >> opt;
		std::cout << "\n";
		if (opt != "3" and opt != "1" and opt != "2")
			std::cout << "\nInvalid command!\n\n";
		else
		{
			if(opt=="3")
				return;
			if (opt == "1")
				AdminMode();
			if (opt == "2")
			{
				while (true)
				{
					if (userFile == 0)
					{
						std::string fileOption;
						std::cout << "File types:\n1.CSV\n2.HTML\n";
						std::cout << "Please choose the file type: ";
						std::cin >> fileOption;
						std::cout << "\n";
						if (fileOption == "1")
						{
							this->userService.chooseRepositoryType(1);
							userFile = 1;
							break;
						}
						else if (fileOption == "2")
						{
							this->userService.chooseRepositoryType(2);
							userFile = 1;
							break;
						}
						else
						{
							std::cout << "\nInvalid command!\n\n";
							continue;
						}
					}
					else
						break;
				}
				UserMode();
			}
				
		}
	}
}

void UI::AdminMode()
{
	std::string opt;
	while (true)
	{
		displayAdminMenu();
		std::cin >> opt;
		std::cout << "\n";
		if (opt == "1")
			handleAdd();
		else if (opt == "2")
			handleRemove();
		else if (opt == "3")
			handleUpdate();
		else if (opt == "4")
			printCoat();
		else if (opt == "5")
			return;
		else
			std::cout << "\nInvalid command!\n\n";
	}
}

void UI::handleBuy()
{
	std::string s;
	while (true)
	{
		std::cout << "Size: ";
		std::cin.ignore();
		std::getline(std::cin, s);
		std::cout << "\n";
		if (s != "XXS" or s != "XS" or s != "S" or s != "M" or s != "L" or s != "XL" or s != "XXL" )
			break;
		else
			std::cout << "\nInvalid size!\n\n";
	}
	
	std::vector<Coat> arr = this->adminService.getCoatList();
	bool ok = true;
	while (ok)
	{
		for (auto i : arr)
		{
			if ((s.size()==0 or i.GetSize()==s) and i.GetQuantity()>0)
			{
				std::cout << i << "\n";
				std::string command = std::string("start ").append(i.GetPhoto());
				system(command.c_str());
				std::string opt;
				std::cout << "\n1. Buy\n";
				std::cout << "2. Next\n";
				std::cout << "3. Exit\n";
				std::cout << "\nYour option: ";
				std::cin >> opt;
				std::cout << "\n";

				if (opt == "1")
				{
					this->userService.addCoatToShoppingBag(i.GetSize(), i.GetColour(), i.GetPrice(), 1, i.GetPhoto());
					std::cout << "Total price: " << this->userService.TotalPrice() << "\n\n";
					int newQuantity = i.GetQuantity()-1;
					this->adminService.updateCoatServ(i.GetSize(), i.GetColour(), i.GetPrice(), newQuantity, i.GetPhoto());
				}
				else if (opt == "2")
					continue;
				else if (opt == "3")
				{
					ok = false;
					break;
				}
				else
					std::cout << "Invalid input!\n\n";
			}
		}
	}
}


void UI::UserMode()
{
	std::string opt;
	while (true)
	{
		displayUserMenu();
		std::cin >> opt;
		std::cout << "\n";
		if (opt == "1")
			handleBuy();
		else if (opt == "2")
			printShoppingBag();
		else if(opt== "3")
			openFile();
		else if (opt == "4")
			return;
		else
			std::cout << "\nInvalid command!\n\n";
	}
}

UI::~UI() = default;

