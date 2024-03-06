#include "service.h"
#include <algorithm>

void Service::addPatient(std::string name, std::string diagnosis, std::string specialization, std::string doctor, std::string date)
{
	Patient p{ name, diagnosis, specialization, doctor, date };
	this->repo.addPatient(p);
}

void Service::addDoctor(std::string name, std::string specialization)
{
	Doctor d{ name, specialization };
	this->repo.addDoctor(d);
}

std::vector<Patient> Service::getPatients(std::string specialization)
{
	std::vector<Patient> patients = this->repo.getPatients();
	std::vector<Patient> result;
	std::string undiagnosed = "undiagnosed";
	for (auto p : patients)
		if (p.getDiagnosis()==undiagnosed or p.getSpecialization()==specialization)
			result.push_back(p);
	std::sort(result.begin(), result.end(), [](Patient p1, Patient p2) {return p1.getDate() < p2.getDate(); });
	return result;
}

std::vector<Patient> Service::getPatientsForDoctor(std::string doctorName)
{
	std::vector<Patient> patients = this->repo.getPatients();
	std::vector<Patient> result;
	for (auto p : patients)
		if (p.getDoctor() == doctorName)
			result.push_back(p);
	std::sort(result.begin(), result.end(), [](Patient p1, Patient p2) {return p1.getDate() < p2.getDate(); });
	return result;
}

void Service::updatePatient(std::string name, std::string diagnosis, std::string specialization, std::string doctor, std::string date)
{
	this->repo.updatePatient(name, diagnosis, specialization, doctor, date);
}

std::vector<int> Service::countSpecialization()
{

	std::vector<Patient> patients = this->repo.getPatients();
	std::vector<int> result;
	int count = 0;
	std::vector<std::string> specializations;
	for (auto p : patients)
	{
		if (std::find(specializations.begin(), specializations.end(), p.getSpecialization()) == specializations.end())
		{
			specializations.push_back(p.getSpecialization());
			count = 0;
			for (auto p1 : patients)
				if (p1.getSpecialization() == p.getSpecialization())
					count++;
			result.push_back(count);
		}
	}
	return result;
}
