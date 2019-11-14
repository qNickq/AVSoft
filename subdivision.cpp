#include "subdivision.h"

Subdivision::Subdivision()
{


}

Subdivision::Subdivision(QString name) : QStandardItem(name)
{
    _name = name;
    _countEmp = 0;
    _avgSalary = 0;
    _salary = 0;
    _employees = new QMap<int, Employee*>();
}

int Subdivision::avgSalary() const
{
    return _avgSalary;
}


int Subdivision::countEmp() const
{
    return _countEmp;
}

void Subdivision::addEmployee(QString name, QString surname, QString patronymic, QString position, int salary)
{
    Employee *employee = new Employee(name, surname,patronymic,position,salary);

    employee->setSubdivisionId(_id);
    employee->setId(_employees->count());

    _salary += salary;
    _employees->insert(employee->id(), employee);
    _countEmp++;
    _avgSalary = _salary / _countEmp;

    this->appendRow(employee);
}

QString Subdivision::name() const
{
    return _name;
}

void Subdivision::setName(const QString &name)
{
    _name = name;
}


Subdivision::~Subdivision()
{

}
