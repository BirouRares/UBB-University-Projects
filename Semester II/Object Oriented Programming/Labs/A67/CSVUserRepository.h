#pragma once
#include "userRepository.h"

class CSVUserRepository : public UserRepository
{
public:
	CSVUserRepository(std::string CSVfileName);
	void writeToFile() override;
	~CSVUserRepository() override;
};