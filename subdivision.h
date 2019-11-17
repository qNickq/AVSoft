#ifndef SUBDIVISION_H
#define SUBDIVISION_H

#include <QMap>
#include "employee.h"

class Subdivision : public QStandardItem
{
public:
    Subdivision();
    Subdivision(QString name);
    ~Subdivision();

    int avgSalary() const;

    int countEmp() const;

    Employee* addEmployee(QString name, QString surname, QString patronymic,QString position, int salary);
    void removeEmployee(Employee*);
    QString name() const;
    void setName(const QString &name);



    QMap<int, Employee *> *employees() const;

private:
    QMap<int, Employee*>* _employees;

    QString _name;
    int _avgSalary;
    int _countEmp;
    int _id;
    int _salary;


};

#endif // SUBDIVISION_H
