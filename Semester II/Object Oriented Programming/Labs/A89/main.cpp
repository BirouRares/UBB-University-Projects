#include "A89.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QWidget w{};
    QHBoxLayout* layoutMain= new QHBoxLayout{};
    //auto layoutMain = new QHBoxLayout{};
    w.setLayout(layoutMain);
    
    layoutMain -> addWidget(new QLabel{ "Type:  " });
    layoutMain->addWidget(new QLineEdit);


    QVBoxLayout* layoutButtons = new QVBoxLayout{};
    //auto layoutButtons = new QVBoxLayout;

    layoutButtons-> addWidget(new QPushButton{ "Cmd1" });
    layoutButtons->addWidget(new QPushButton{ "Cmd2" });
    layoutButtons->addWidget(new QPushButton{ "Cmd3" });

    layoutMain->addLayout(layoutButtons);


    auto form= new QFormLayout;
    form->addRow("Name", new QLineEdit);
    form->addRow("Age", new QLineEdit);
    form->addRow("Job", new QLineEdit);

    layoutMain->addLayout(form);

    
    auto lst = new QListWidget;
    vector <string> v={ "Item 1", "Item 2", "Item 3", "1", "2"};

    for (const auto& s : v)
    {
		lst->addItem(QString::fromStdString(s));
	}
    
    lst->addItem("3");
    lst->addItem(new QListWidgetItem{ "4"});
    layoutMain-> addWidget(lst);
    w.show();



    //QLabel label{ "Hello World!" };
    //label.show();

    //QPushButton button{ "Say hello" };
    //button.show();
    


    return a.exec();
}
