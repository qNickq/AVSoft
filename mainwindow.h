#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "company.h"

#include "cmdadddepartment.h"
#include "cmdremovedepartment.h"

#include "cmdaddemployee.h"
#include "cmdremoveemployee.h"

#include "cmdeditemployee.h"
#include "cmdeditdepartment.h"


#include "centralwidget.h"
#include "employeeeditor.h"

#include <QMainWindow>
#include <QObject>
#include <QtWidgets>
#include <QFile>
#include <QtXml>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setCurrentDep(const QModelIndex &index);
    void setCurrentEmp(const QModelIndex &index);

    void addDepartment(QString name);
    void editDepartment(QString name);
    void removeDepartment();

    void addEmployee();
    void editCompany(const QModelIndex &index);
    void removeEmployee();

    void openFile();

    void openNewCompanyDialog();
    void newCompany();


    void openNewEployeeDialog();

private:

    Company* _company;
    Department * _currentDep;
    Employee * _currentEmp;

    QList<Command*> _history;
    QListIterator<Command*> _iterator;

    CentralWidget* _centralWidget;
    EmployeeEditor * _employeeEditor;

    QUrl _pathXML;

    void executeCommand(Command* command);
    void undoCommand();
    void redoCommand();
    void clearHistory();

    void createActions();
    void editEmployee();
    void saveFile();
};

#endif // MAINWINDOW_H
