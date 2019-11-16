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

QString Employee::patronymic() const
{
    return _patronymic;
}

void Employee::setPatronymic(const QString &value)
{
    _patronymic = value;
}

QString Employee::position() const
{
    return _position;
}

void Employee::setPosition(const QString &value)
{
    _position = value;
}

int Employee::salary() const
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

