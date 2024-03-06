#include "Paint.h"

Paint::Paint(Service& s, QWidget *parent)
	:service{ s }, QMainWindow(parent)
{
	ui.setupUi(this);
}

Paint::~Paint()
{}

void Paint::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setBrush(Qt::SolidPattern);

	QPen pen;
	pen.setColor(Qt::green);
	pen.setWidth(5);
	painter.setPen(pen);
	int pozUp=10;
	int pozRight=10;
	std::vector<int> v= this->service.countSpecialization();
	for (int i = 0; i < v.size(); i++)
	{
		pozUp = 10;
		for (int j = 0; j < v[i]; j++)
		{
			//painter.drawText(80, 120, QString::number(v[i]));
			painter.drawRect(QRect(pozRight, pozUp, 30, 30));
			pozUp += 30;
		}
		pozRight += 30;
		
	}
}

void Paint::update()
{
	repaint();
}
