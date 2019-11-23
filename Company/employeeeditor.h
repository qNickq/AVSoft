#ifndef EMPLOYEEEDITOR_H
#define EMPLOYEEEDITOR_H

#include <QDialog>
#include <QRegExpValidator>
#include <QStringList>

#include "employee.h"

namespace Ui {
class EmployeeEditor;
}

class EmployeeEditor : public QDialog
{
    Q_OBJECT

public:
     EmployeeEditor(Employee * emp = nullptr, QWidget *parent = nullptr);
    ~EmployeeEditor();

    QStringList getData();

private:
    Employee* _employee;
    Ui::EmployeeEditor *ui;

};

#endif // EMPLOYEEEDITOR_H
