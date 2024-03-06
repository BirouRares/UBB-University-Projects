#pragma once
#include <string>
#include <vector>
class Patient
{
private:
	std::string name;
	std::string diagnosis;
	std::string specialization;
	std::string doctor;
	std::string date;
public:
	Patient();
	Patient(std::string name, std::string diagnosis, std::string specialization, std::string doctor, std::string date);

	std::string getName() { return name; }
	std::string getDiagnosis() { return diagnosis; }
	std::string getSpecialization() { return specialization; }
	std::string getDoctor() { return doctor; }
	std::string getDate() { return date; }

	void setName(std::string name) { this->name = name; }
	void setDiagnosis(std::string diagnosis) { this->diagnosis = diagnosis; }
	void setSpecialization(std::string specialization) { this->specialization = specialization; }
	void setDoctor(std::string doctor) { this->doctor = doctor; }
	void setDate(std::string date) { this->date = date; }

	friend std::istream& operator>>(std::istream& is, Patient& p);
	friend std::ostream& operator<<(std::ostream& os, Patient& p);
};

