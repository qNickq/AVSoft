#include "cmdaddemployee.h"

CmdAddEmployee::CmdAddEmployee(Subdivision * subdivision, QString name, QString surname, QString patronymic, QString position, int salary) : Command()
{
    _subdivision = subdivision;
    _name = name;
    _surname = surname;
    _patronymic = patronymic;
    _position = position;
    _salary = salary;
}

void CmdAddEmployee::execute()
{
    _subdivision->addEmployee(_name, _surname, _patronymic, _position,_salary);
}

CmdAddEmployee::~CmdAddEmployee()
{
}
