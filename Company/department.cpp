#include "department.h"

Department::Department(QString name) : QStandardItem(name)
{
    _name = name;
    _countEmp = 0;
    _avgSalary = 0;
    _salary = 0;
    _employees = new QMap<QString, Employee*>();

    setColumnCount(3);
}

Department::Department(const Department &department)
{
    _name = department.name();
    _countEmp = department.countEmp();
    _avgSalary = department.avgSalary();

    if(_countEmp != 0)
    {
        _salary  = department.avgSalary() / department.countEmp();
    }
    else
    {
        _salary = 0;
    }

    _employees = new QMap<QString, Employee*>(*department.employees());
}

int Department::avgSalary() const
{
    return _avgSalary;
}


int Department::countEmp() const
{
    return _countEmp;
}

Employee* Department::addEmployee(QString name, QString surname, QString middleName, QString function, int salary)
{
    Employee *employee = new Employee(name, surname, middleName, function, salary);

    _employees->insert(employee->id(), employee);

    _salary += salary;
    _countEmp++;
    _avgSalary = _salary / _countEmp;

    this->appendRow(employee);

    QModelIndex in(model()->index(employee->row() , 1, index()));
    model()->setData(in, employee->function(), Qt::DisplayRole);

    QModelIndex in2(model()->index(employee->row() , 2, index()));
    model()->setData(in2, employee->salary(), Qt::DisplayRole);

    return employee;
}

QString Department::name() const
{
    return _name;
}

void Department::setName(QString name)
{
    _name = name;
    setData(name, Qt::DisplayRole);
}

void Department::removeEmployee(QString id)
{
    Employee * emp = employees()->value(id);

    _salary -= emp->salary();
    _countEmp--;

    if(_countEmp <= 0)
    {
        _avgSalary = 0;
    }
    else
    {
        _avgSalary = _salary / _countEmp;
    }
    this->removeRow(emp->row());

    _employees->remove(id);
}

QMap<QString, Employee *> *Department::employees() const
{
    return _employees;
}

Department::~Department()
{
    QMapIterator<QString, Employee*> i(*_employees);

    while (i.hasNext())
    {
        i.next();
        removeEmployee(i.key());
    }
    _employees->clear();
    delete  _employees;
}
