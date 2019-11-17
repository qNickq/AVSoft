#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "company.h"
#include "cmdaddsub.h"
#include "cmdaddemployee.h"
#include "newemployeewidget.h"
#include "centralwidget.h"


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

    void executeCommand(Command* command);
    void undoCommand();
    void redoCommand();
    void clearHistory();
public slots:
    void addSubdivision(QString name);
    void addEmployee(QString name, QString surname, QString patronymic, QString position, int salary);
    void openNewCompanyDialog();
    void openCompany();
    void newCompany(QString);
    void setCurSub(QString currentSubName);
    void openNewEployeeDialog();

private:

    Company* _company;

    QList<Command*> _history;
    QListIterator<Command*> _iterator;

    CentralWidget* _centralWidget;

    NewEmployeeWidget* _newEmployeeWidget;
    Subdivision * _currentSub;
    QUrl _pathXML;

    void createActions();
    void createStatusBar();

    bool maybeSave();
    void saveFile();
    void setCurrentFile(const QString &fileName);
};

#endif // MAINWINDOW_H
