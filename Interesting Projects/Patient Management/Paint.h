#pragma once

#include <QMainWindow>
#include "ui_Paint.h"
#include <QPainter>
#include "service.h"
#include "Observer.h"

class Paint : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	Paint(Service& s, QWidget *parent = nullptr);
	~Paint();

	virtual void paintEvent(QPaintEvent* event);

private:
	Ui::PaintClass ui;
	Service& service;
public:
	void update() override;
};
