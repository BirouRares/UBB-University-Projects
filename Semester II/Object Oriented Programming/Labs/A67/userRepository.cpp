#include "userRepository.h"

UserRepository::UserRepository()
{}

UserRepository::~UserRepository() = default;

void UserRepository::updateCoatUserRepo(Coat coat)
{
	int k = 0;
	for (auto c : this->coatList)
	{
		if (c.GetPhoto() == coat.GetPhoto())
		{
			Coat newcoat = Coat(coat.GetSize(), coat.GetColour(), coat.GetPrice(), coat.GetQuantity(), coat.GetPhoto());
			this->coatList.at(k) = newcoat;
			this->writeToFile();
			return;
		}
		k++;
	}
}

void UserRepository::addCoatUserRepo(Coat coat)
{
	this->coatList.push_back(coat);
	this->writeToFile();
}

std::vector<Coat> UserRepository::getCoatList()
{
	return this->coatList;
}

std::string UserRepository::getFileName()
{
	return this->fileName;
}