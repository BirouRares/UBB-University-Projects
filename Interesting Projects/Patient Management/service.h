#pragma once
#include "repository.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
class Service
{
private:
	Repository& repo;
public:
	Service(Repository& repo) : repo{ repo } {}

	std::vector<Patient> getPatients(std::string specialization);
	std::vector<Patient> getPatientsForDoctor(std::string doctorName);
	std::vector<Doctor> getDoctors() { return this->repo.getDoctors(); }
	std::vector<Patient> getAllPatients() { return this->repo.getPatients(); }
	std::vector<int> countSpecialization();



	void updatePatient(std::string name, std::string diagnosis, std::string specialization, std::string doctor, std::string date);
	void addPatient(std::string name, std::string diagnosis, std::string specialization, std::string doctor, std::string date);
	void addDoctor(std::string name, std::string specialization);
};

