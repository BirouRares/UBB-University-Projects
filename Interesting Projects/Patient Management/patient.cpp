#include "patient.h"
#include <sstream>
#include <string>

Patient::Patient()
{
	this->name = "";
	this->diagnosis = "";
	this->specialization = "";
	this->doctor = "";
	this->date = "";
}
Patient::Patient(std::string name, std::string diagnosis, std::string specialization, std::string doctor, std::string date)
{
	this->name = name;
	this->diagnosis = diagnosis;
	this->specialization = specialization;
	this->doctor = doctor;
	this->date = date;
}

std::vector<std::string> tokenize1(const std::string& str, char delimiter)
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

std::istream& operator>>(std::istream& is, Patient& p)
{
	std::string line;
	std::getline(is, line);
	if (line.empty())
		return is;
	std::vector<std::string> tokens;
	tokens = tokenize1(line, ',');
	p.name = tokens[0];
	p.diagnosis = tokens[1];
	p.specialization = tokens[2];
	p.doctor = tokens[3];
	p.date = tokens[4];
	return is;
}
std::ostream& operator<<(std::ostream& os, Patient& p)
{
	os << p.name << "," << p.diagnosis << "," << p.specialization << "," << p.doctor << "," << p.date << "\n";
	return os;
}