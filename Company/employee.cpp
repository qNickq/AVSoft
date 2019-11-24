#include "employee.h"

Employee::Employee(QString name, QString surname, QString middleName, QString function, int salary)
    :QStandardItem(surname + ' ' + name + ' ' + middleName)
{

    _name = name;
    _surname = surname;
    _middleName = middleName;
    _function = function;
    _salary = salary;
    _id = name+surname+middleName+function;
}

QString Employee::name() const
{
    return _name;
}

void Employee::setName(const QString &value)
{
    _name = value;
}

QString Employee::surname() const
{
    return _surname;
}

void Employee::setSurname(const QString &value)
{
    _surname = value;
}

QString Employee::middleName() const
{
    return _middleName;
}

void Employee::setMiddleName(const QString &value)
{
    _middleName = value;
}

QString Employee::function() const
{
    return _function;
}

void Employee::setFunction(const QString &value)
{
    _function = value;
}

int Employee::salary() const
{
    return _salary;
}

void Employee::setSalary(int value)
{
    _salary = value;
}

QString Employee::id() const
{
    return _id;
}

void Employee::setId(QString id)
{
    _id = id;
}

void Employee::setData(const QVariant &value, int role)
{
    QModelIndex in(model()->index(row() , 1, parent()->index()));
    model()->setData(in, _function, role);

    QModelIndex in2(model()->index(row() , 2, parent()->index()));
    model()->setData(in2, _salary, role);

    QStandardItem::setData(value, role);

    emitDataChanged();
}

