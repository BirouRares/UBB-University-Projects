#pragma once
#include "domain.h"
#include <vector>
#include <string>

class UserRepository {
protected:
	std::vector<Coat> coatList;
	std::string fileName;

public:
	UserRepository();
	virtual void addCoatUserRepo(Coat coat) ;
	virtual void updateCoatUserRepo(Coat coat);
	virtual std::vector<Coat> getCoatList();
	virtual std::string getFileName();
	virtual void writeToFile() = 0;
	virtual ~UserRepository();
};
