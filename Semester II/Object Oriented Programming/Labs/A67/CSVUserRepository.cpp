#include "CSVUserRepository.h"
#include <fstream>

CSVUserRepository::CSVUserRepository(std::string CSVfileName)
{
	this->fileName = CSVfileName;
}

void CSVUserRepository::writeToFile()
{
	std::ofstream fileOut(fileName);
	if(!coatList.empty())
		for (auto coat : coatList)
			fileOut << coat << "\n";
	fileOut.close();
}

CSVUserRepository::~CSVUserRepository() = default;