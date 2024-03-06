#include "repository.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>

Repository::Repository()
{
	this->loadFromFile();
}
Repository::~Repository()
{
	this->saveToFile();
}
void Repository::addObserver(Observer* o)
{
	this->observers.push_back(o);
}
void Repository::notify()
{
	for (auto o : this->observers)
		o->update();
}
void Repository::loadFromFile()
{
	std::string file1 = "doctors.txt";
	std::string file2 = "patients.txt";

	if (!file1.empty())
	{
		Doctor d;
		std::ifstream fin1(file1);
		while(fin1>>d)
			this->doctors.push_back(d);
		fin1.close();
	}
	if (!file2.empty())
	{
		Patient p;
		std::ifstream fin2(file2);
		while (fin2 >> p)
			this->patients.push_back(p);
		fin2.close();
	}
}

void Repository::saveToFile()
{
	std::string file1 = "doctors.txt";
	std::string file2 = "patients.txt";

	if (!file1.empty())
	{
		std::ofstream fout1(file1);
		for (auto d : this->doctors)
			fout1 << d;
		fout1.close();
	}
	if (!file2.empty())
	{
		std::ofstream fout2(file2);
		for (auto p : this->patients)
			fout2 << p;
		fout2.close();
	}
}

void Repository::updatePatient(std::string name, std::string diagnosis, std::string specialization, std::string doctor, std::string date)
{
	for(auto& p :this->patients)
		if (p.getName() == name)
		{
			p.setDiagnosis(diagnosis);
			p.setSpecialization(specialization);
			p.setDoctor(doctor);
			p.setDate(date);
		}
	this->notify();
}