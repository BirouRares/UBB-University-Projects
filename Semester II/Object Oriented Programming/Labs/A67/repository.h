#pragma once
#include <vector>
#include <cstdlib>
#include "domain.h"
#include <string>

class Repository
{
private:
	std::vector<Coat> administratorList;
	std::string fileName;
public:
	void loadEntitiesFromFile();
	void writeEntitiesToFile();

	Repository(std::string fileName);

	void addCoatRepo(Coat c);
	void deleteCoatRepo(std::string size, std::string colour, std::string photo);
	void updateCoatRepo(std::string photo, Coat newCoat);
	std::vector<Coat> getCoatList() const;
	~Repository();// destructor
};
