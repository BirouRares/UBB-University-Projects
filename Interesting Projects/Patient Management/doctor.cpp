#include "doctor.h"
#include <sstream>
#include <string>

Doctor::Doctor()
{
	this->name = "";
	this->specialization = "";
}
Doctor::Doctor(std::string name, std::string specialization)
{
	this->name = name;
	this->specialization = specialization;
}
std::vector<std::string> tokenize(const std::string& str, char delimiter)
{
	std::vector<std::string> tokens;
	std::istringstream stream(str);
	std::string token;
	while (std::getline(stream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::istream& operator>>(std::istream& is, Doctor& d)
{
	std::string line;
	std::getline(is, line);
	if (line.empty())
		return is;
	std::vector<std::string> tokens;
	tokens = tokenize(line, ',');
	d.name = tokens[0];
	d.specialization = tokens[1];
	return is;
}

std::ostream& operator<<(std::ostream& os, Doctor& d)
{
	os << d.name << "," << d.specialization << "\n";
	return os;
}