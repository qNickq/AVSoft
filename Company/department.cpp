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
    employee->setData(surname + ' ' + name + ' ' + middleName, Qt::DisplayRole);

    QModelIndex in(model()->index(row() , 3));
    model()->setData(in, _avgSalary, Qt::DisplayRole);

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

    if(_countEmp)
    {
        _avgSalary = _salary / _countEmp;
    }
    else
    {
        _avgSalary = 0;
    }

    if(model()!= nullptr)
    {
        QModelIndex in(model()->index(row() , 3));
        model()->setData(in, _avgSalary, Qt::DisplayRole);
    }
    this->removeRow(emp->row());

    _employees->remove(id);
}

void Department::editEmployee(QString id, QString name, QString surname, QString middleName, QString function, int salary)
{
    Employee * emp = _employees->value(id);

    _salary -= emp->salary();
    _salary += salary;

    emp->setName(name);
    emp->setSurname(surname);
    emp->setMiddleName(middleName);
    emp->setFunction(function);
    emp->setSalary(salary);

    _avgSalary = _salary / _countEmp;

    QModelIndex in(model()->index(row() , 3));
    model()->setData(in, _avgSalary, Qt::DisplayRole);

    QString newId = name + surname + middleName + function;

    emp->setId(newId);

    if(emp)
    {
        _employees->remove(id);
    }
    _employees->insert(newId, emp);

    emp->setData(surname + ' ' + name + ' ' + middleName, Qt::DisplayRole);

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
