#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "company.h"
#include "newcompanywidget.h"
#include "newemployeewidget.h"
#include "centralwidget.h"

#include <QMainWindow>
#include <QObject>
#include <QtWidgets>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void addSubdivision(QString name);
    void addEmployee();
    void openNewCompanyDialog();
    void openNewEmployeeDialog();
    void openCompany();
    void newCompany(QString, QString);
    void setCurSub(QString);
private:
    CentralWidget* _centralWidget;
    Company* _company;

    NewCompanyWidget _newCompanyWidget;
    NewEmployeeWidget _newEmployeeWidget;

    QString _curSub;

    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
};

#endif // MAINWINDOW_H
