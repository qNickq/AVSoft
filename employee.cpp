#include "employee.h"

Employee::Employee()
{
}

Employee::Employee(QString name, QString surname, QString patronymic, QString position, int salary)
    :QStandardItem(name + ' ' + surname + ' ' + patronymic)
{
    _name = name;
    _surname = surname;
    _patronymic = patronymic;
    _position = position;
    _salary = salary;

}

QString Employee::getName() const
{
    return _name;
}

void Employee::setName(const QString &value)
{
    _name = value;
}

QString Employee::getSurname() const
{
    return _surname;
}

void Employee::setSurname(const QString &value)
{
    _surname = value;
}

QString Employee::getPatronymic() const
{
    return _patronymic;
}

void Employee::setPatronymic(const QString &value)
{
    _patronymic = value;
}

QString Employee::getPosition() const
{
    return _position;
}

void Employee::setPosition(const QString &value)
{
    _position = value;
}

int Employee::getSalary() const
{
    return _salary;
}

void Employee::setSalary(int value)
{
    _salary = value;
}

int Employee::getSubdivisionId() const
{
    return _subdivisionId;
}

void Employee::setSubdivisionId(int subdivisionId)
{
    _subdivisionId = subdivisionId;
}

int Employee::id() const
{
    return _id;
}

void Employee::setId(int id)
{
    _id = id;
}

