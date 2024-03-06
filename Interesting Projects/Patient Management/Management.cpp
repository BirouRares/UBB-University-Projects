#include "Management.h"
#include <algorithm>
#include <QMessageBox>
#include <cmath>
#include <QFont>

Management::Management(Service& s, Doctor d, QWidget *parent)
    :service{ s }, doctor{ d }, QMainWindow(parent)
{
    ui.setupUi(this);
    populateList();
	connectSignals();
}

void Management::update()
{
	this->populateList();
}

void Management::connectSignals()
{
	QObject::connect(ui.checkBox, &QCheckBox::stateChanged, this, &Management::handleCheckBoxStateChanged);
	QObject::connect(ui.addButton, &QPushButton::clicked, this, &Management::handleAdd);
	QObject::connect(ui.updateButton, &QPushButton::clicked, this, &Management::handleUpdate);
}

void Management::handleUpdate()
{
	QString name = this->ui.nameLine->text();
	QString diagnosis = this->ui.diagnosisLine->text();
	QString specialization = this->ui.specializationLine->text();
	QString doctor = this->ui.doctorLine->text();
	QString date = this->ui.dateLine->text();

	std::string diagnosisStr = diagnosis.toStdString();
	std::string specializationStr = specialization.toStdString();
	std::string doctorStr = doctor.toStdString();
	std::string nameStr = name.toStdString();
	std::string dateStr = date.toStdString();

	if (diagnosisStr == "undiagnosed")
	{
		QMessageBox::critical(this, "Error", "Invalid diagnosis!");
		return;
	}
	if (nameStr.empty())
	{
		QMessageBox::critical(this, "Error", "Invalid name!");
		return;
	}
	if(diagnosisStr.empty())
		diagnosisStr = " ";
	if (specializationStr.empty())
		specializationStr = " ";
	if (doctorStr.empty())
		doctorStr = " ";
	if (dateStr.empty())
		dateStr = " ";

	std::vector<Patient> patients = this->service.getAllPatients();
	for (auto p : patients)
	{
		if (p.getName() == nameStr)
		{
			if(p.getDoctor() == this->doctor.getName() or p.getDiagnosis()=="undiagnosed")
				this->service.updatePatient(nameStr, diagnosisStr, specializationStr, doctorStr, dateStr);
			else
			{
				QMessageBox::critical(this, "Error", "You can't update this patient!");
				return;
			}
		}
	}
		
	this->ui.checkBox->setCheckState(Qt::Unchecked);
	this->populateList();

	this->ui.nameLine->clear();
	this->ui.diagnosisLine->clear();
	this->ui.specializationLine->clear();
	this->ui.doctorLine->clear();
	this->ui.dateLine->clear();
}

void Management::handleAdd()
{
	QString name = this->ui.nameLine->text();
	QString diagnosis = this->ui.diagnosisLine->text();
	QString specialization = this->ui.specializationLine->text();
	QString doctor = this->ui.doctorLine->text();
	QString date = this->ui.dateLine->text();
	if (name.isEmpty())
	{
		QMessageBox::critical(this, "Error", "No Name!");
		return;
	}
	std::string dateStr= date.toStdString();
	if (dateStr < "2023.07.10")
	{
		QMessageBox::critical(this, "Error", "Invalid date!");
		return;
	}
	std::string diagnosisStr = diagnosis.toStdString();
	std::string specializationStr = specialization.toStdString();
	std::string doctorStr = doctor.toStdString();
	std::string nameStr = name.toStdString();
	if(diagnosisStr.empty())
		diagnosisStr = "undiagnosed";
	if (specializationStr.empty())
		specializationStr = " ";
	if (doctorStr.empty())
		doctorStr = " ";
	this->service.addPatient(nameStr, diagnosisStr, specializationStr, doctorStr, dateStr);
	this->ui.checkBox->setCheckState(Qt::Unchecked);
	this->populateList();
	
	this->ui.nameLine->clear();
	this->ui.diagnosisLine->clear();
	this->ui.specializationLine->clear();
	this->ui.doctorLine->clear();
	this->ui.dateLine->clear();
	
}

void Management::handleCheckBoxStateChanged(int status)
{
	if (status == Qt::Checked)
		this->populateListDoctors();
	else
		this->populateList();
}

void Management::populateList()
{
	this->ui.listWidget->clear();
	std::vector<Patient> patients = this->service.getPatients(this->doctor.getSpecialization());
	for (auto p : patients)
	{
		QString itemInList = QString::fromStdString(p.getName() + " | " + p.getDiagnosis() + " | " +p.getSpecialization()+" | "+p.getDoctor()+" | " + p.getDate());
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		if(this->doctor.getName()==p.getDoctor())
			item->setBackground(Qt::green);
		this->ui.listWidget->addItem(item);
	}
}

void Management::populateListDoctors()
{
	this->ui.listWidget->clear();
	std::vector<Patient> patients = this->service.getPatientsForDoctor(this->doctor.getName());
	for (auto p : patients)
	{
		QString itemInList = QString::fromStdString(p.getName() + " | " + p.getDiagnosis() + " | " + p.getSpecialization() + " | " + p.getDoctor() + " | " + p.getDate());
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		this->ui.listWidget->addItem(item);
	}
}
