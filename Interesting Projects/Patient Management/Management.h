#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Management.h"
#include "service.h"
class Management : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    Management(Service& s,Doctor d, QWidget *parent = nullptr);

private:
    Ui::ManagementClass ui;
    Service& service;
    Doctor doctor;
    
    void populateList();
    void connectSignals();
    void populateListDoctors();
    void handleCheckBoxStateChanged(int status);
    void handleAdd();
    void handleUpdate();

    void update() override;
};
