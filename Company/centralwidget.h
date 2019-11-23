#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QObject>
#include <QtWidgets>

namespace Ui
{
    class CentralWidget;
}

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();

    QTreeView *view() const;

    QModelIndex currentIndex () const;

    void setDep(QString name, int count, int salary);

signals:
    void addEmployee();
    void removeEmployee();

    void addDepartment(QString);
    void editDepartment(QString);
    void removeDepartment();

    void curDepartment(const QModelIndex &index);
    void curEmployee(const QModelIndex &index);

public slots:
    void setEnableBtns();
    void sendAddDep();
    void sendEditDep();

private:
     Ui::CentralWidget * ui;

     QModelIndex _currentIndex;
};

#endif // CENTRALWIDGET_H
