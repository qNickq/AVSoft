#include "subdivision.h"

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

Employee* Subdivision::addEmployee(QString name, QString surname, QString patronymic, QString position, int salary)
{
    Employee *employee = new Employee(name, surname,patronymic,position,salary);

    _salary += salary;
    _employees->insert(_countEmp, employee);
    employee->setId(_countEmp);
    _countEmp++;
    _avgSalary = _salary / _countEmp;

    this->appendRow(employee);
    return employee;
}

QString Subdivision::name() const
{
    return _name;
}

void Subdivision::setName(const QString &name)
{
    _name = name;
}

void Subdivision::removeEmployee(Employee * emp)
{

    _salary -= emp->salary();
    _employees->remove(emp->id());
    _countEmp--;
    if(_countEmp <= 0) _avgSalary = 0;
    else
    {
        _avgSalary = _salary / _countEmp;
    }

    this->removeRow(emp->row());
}

QMap<int, Employee *> *Subdivision::employees() const
{
    return _employees;
}


Subdivision::~Subdivision()
{
    QMap<int, Employee*>::iterator i = _employees->begin();
    while (i != _employees->end())
    {
         delete i.value();
         ++i;
    }
    _employees->clear();
    delete  _employees;
}
