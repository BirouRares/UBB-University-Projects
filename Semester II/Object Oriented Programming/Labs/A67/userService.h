#pragma once
#include "userRepository.h"

class UserService
{
private:
	UserRepository* userRepo;
	int total;
public:
	UserService();
	UserService(UserRepository* userRepo);
	int TotalPrice();
	void updateCoatInShoppingBag(std::string size, std::string colour, int price, int quantity, std::string photo);
	void addCoatToShoppingBag(std::string size, std::string colour, int price, int quantity, std::string photo);
	std::vector<Coat> getCoatList();
	std::string getFileName();
	void chooseRepositoryType(int fileType);
	~UserService();
};
