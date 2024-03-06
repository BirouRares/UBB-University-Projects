#include "Management.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include "repository.h"
#include <QSortFilterProxyModel>
#include <vector>
#include <QMessageBox>
#include <QAbstractTableModel>
#include <QtWidgets/QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Paint.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{};
    Service service{ repo };

    std::vector<Doctor> doctors = service.getDoctors();
    for (auto& d : doctors)
    {
        Management* m = new Management{ service, d };
        repo.addObserver(m);
        m->setWindowTitle(QString::fromStdString(d.getName()));
        m->show();
    }
    Paint* p = new Paint{ service };
    repo.addObserver(p);
    p->show();
    return a.exec();
}
