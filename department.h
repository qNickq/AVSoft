#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QMap>
#include <QObject>
#include "employee.h"

class Department : public QStandardItem
{
public:
    Department(QString name);
    Department(const Department& department);
    ~Department();

    int avgSalary() const;

    int countEmp() const;

    Employee* addEmployee(QString name, QString surname, QString middleName,QString function, int salary);

    void removeEmployee(QString id);

    QString name() const;

    void setName(QString name);

    QMap<QString, Employee *> *employees() const;

private:
    QMap<QString, Employee*>* _employees;

    QString _name;
    int _avgSalary;
    int _countEmp;
    int _salary;
};

#endif // DEPARTMENT_H
