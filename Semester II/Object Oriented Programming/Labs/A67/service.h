#pragma once
#include "repository.h"

class Service
{
private: 
	Repository& repo;

public: 
	Service(Repository& repo);
	void addCoatServ(std::string size, std::string colour, int price, int quantity, std::string photo);
	void removeCoatServ(std::string size, std::string colour, std::string photo);
	void updateCoatServ(std::string size, std::string colour, int price, int quantity, std::string photo);
	std::vector<Coat> getCoatList();
	~Service();
};