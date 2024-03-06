#pragma once
#include <string>
#include <vector>
class Doctor
{
private:
	std::string name;
	std::string specialization;
public:
	Doctor();
	Doctor(std::string name, std::string specialization);

	std::string getName() { return name; }
	std::string getSpecialization() { return specialization; }

	friend std::istream& operator>>(std::istream& is, Doctor& d);
	friend std::ostream& operator<<(std::ostream& os, Doctor& d);

};

