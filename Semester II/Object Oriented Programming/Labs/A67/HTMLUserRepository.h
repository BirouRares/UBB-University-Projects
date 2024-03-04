#pragma once
#include "userRepository.h"

class HTMLUserRepository : public UserRepository
{
public:
	HTMLUserRepository(std::string HTMLfileName);
	void writeToFile() override;
	~HTMLUserRepository() override;
};