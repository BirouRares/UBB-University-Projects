#pragma once
#include "patient.h"
#include "doctor.h"
#include <iostream>
#include <string>
#include <vector>
#include "subject.h"
#include "observer.h"
class Repository : public Subject
{
private:
	std::vector<Patient> patients;
	std::vector<Doctor> doctors;
	std::vector<Observer*> observers;
public:
	Repository();
	~Repository();
	void addObserver(Observer* o) override;
	void notify() override;

	void loadFromFile();
	void saveToFile();

	void addPatient(Patient p) { this->patients.push_back(p); this->notify();}
	void addDoctor(Doctor d) { this->doctors.push_back(d); this->notify();}

	void updatePatient(std::string name, std::string diagnosis, std::string specialization, std::string doctor, std::string date);

	std::vector<Patient> getPatients() { return this->patients; }
	std::vector<Doctor> getDoctors() { return this->doctors; }
};

