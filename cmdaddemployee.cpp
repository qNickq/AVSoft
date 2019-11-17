#include "cmdaddemployee.h"

CmdAddEmployee::CmdAddEmployee(Company * company,QString subname, QString name, QString surname, QString patronymic, QString position, int salary) : Command()
{
    _company = company;
    _subname = subname;
    _name = name;
    _surname = surname;
    _patronymic = patronymic;
    _position = position;
    _salary = salary;
}

void CmdAddEmployee::execute()
{
    _subdivision = _company->subdivisions()->value(_subname);
    _employee = _subdivision->addEmployee(_name, _surname, _patronymic, _position,_salary);
}

void CmdAddEmployee::undo()
{

    _subdivision->removeEmployee(_employee);
}

void CmdAddEmployee::redo()
{
    _subdivision = _company->subdivisions()->value(_subname);
    _employee = _subdivision->addEmployee(_name, _surname, _patronymic, _position,_salary);
}
