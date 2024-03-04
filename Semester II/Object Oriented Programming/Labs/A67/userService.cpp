#include "userService.h"
#include "errors.h"
#include "CSVUserRepository.h"
#include "HTMLUserRepository.h"

UserService::UserService()
{}

UserService::UserService(UserRepository* userRepo)
{
	this->userRepo = userRepo;
	this->total=0;
}

int UserService::TotalPrice()
{
	return this->total;
}

void UserService::updateCoatInShoppingBag(std::string size, std::string colour, int price, int quantity, std::string photo)
{
	Coat c = Coat(size, colour, price, quantity, photo);
	try
	{
		this->userRepo->updateCoatUserRepo(c);
	}
	catch (RepoError e)
	{
		throw e;
	}
}

void UserService::addCoatToShoppingBag(std::string size, std::string colour, int price, int quantity, std::string photo)
{
	Coat c = Coat(size, colour, price, 1, photo);
	try
	{
		int ok = false;
		std::vector <Coat> coatList = this->userRepo->getCoatList();
		for (auto i : coatList)
		{
			if (i.GetColour() == colour and i.GetPrice() == price and i.GetPhoto() == photo and i.GetSize()==size)
			{
				ok=true;
				int q=i.GetQuantity()+1;
				Coat c2 = Coat(size, colour, price,q, photo);
				this->userRepo->updateCoatUserRepo(c2);
			}
				
		}
		if (ok == false)
			this->userRepo->addCoatUserRepo(c);
		this->total += price;
	}
	catch (RepoError e)
	{
		throw e;
	}
}

std::vector<Coat> UserService::getCoatList()
{
	return this->userRepo->getCoatList();
}

std::string UserService::getFileName()
{
	return this->userRepo->getFileName();
}

void UserService::chooseRepositoryType(int fileType)
{
	if (fileType == 1)
	{
		std::string file = "coatList.csv";
		auto repo = new CSVUserRepository{ file };
		this->userRepo = repo;
	}
	else if (fileType)
	{
		std::string file = "coatList.html";
		auto repo = new HTMLUserRepository{ file };
		this->userRepo = repo;
	}
}

UserService::~UserService()
{
	delete this->userRepo;
}