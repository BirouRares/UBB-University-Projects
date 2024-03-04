#include "repository.h"
#include "errors.h"
#include "validation.h"
#include <algorithm>
#include <fstream>


Repository::Repository(std::string fileName)
{
	this->fileName = fileName;
}

void Repository::loadEntitiesFromFile()
{
	if (!fileName.empty())
	{
		Coat fileCoat;
		std::ifstream fileIn(fileName);
		while (fileIn >> fileCoat)
		{
			if(std::find(administratorList.begin(), administratorList.end(), fileCoat)== administratorList.end())
				administratorList.push_back(fileCoat);
		}
		fileIn.close();
	}
}

void Repository::writeEntitiesToFile()
{
	if (!fileName.empty())
	{
		std::ofstream fileOut(fileName);
		for (auto coat : administratorList)
		{
			fileOut << coat<<"\n";
		}
		fileOut.close();
	}
}

void Repository::addCoatRepo(Coat c)
{
	vector <Coat> arr= this->getCoatList();
	for (auto i : arr)
		if (i.GetPhoto() == c.GetPhoto())
			throw RepoError("The coat already exists!");
	try
	{
		Validator::validateCoat(c);
		this->administratorList.push_back(c);
		this->writeEntitiesToFile();
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << "\n\n";
	}
		
}

void Repository::deleteCoatRepo(std::string size, std::string colour, std::string photo)
{
	auto it = std::remove_if(administratorList.begin(), administratorList.end(), [size, colour, photo](Coat c) {return c.GetSize() == size and c.GetColour() == colour and c.GetPhoto() == photo; });
	if (it == administratorList.end())
		throw RepoError("The coat does not exist!");
	administratorList.pop_back();
	this->writeEntitiesToFile();
}

void Repository::updateCoatRepo(std::string photo, Coat newCoat)
{
	int k = 0;
	for (auto i : administratorList)
	{
		if (i.GetPhoto() == photo)
		{
			try
			{
				Validator validate;
				validate.validateCoat(newCoat);
				administratorList.at(k) = newCoat;
				this->writeEntitiesToFile();
				return;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << "\n";
			}
		}
		k++;
	}
	throw RepoError("The coat does not exist!");
}

std::vector<Coat> Repository::getCoatList() const
{
	return this-> administratorList;
}

Repository::~Repository() = default;
