#include "cmdaddemployee.h"

CmdAddEmployee::CmdAddEmployee(Company * company, Department * department, QString name, QString surname, QString middleName, QString function, int salary)
    : Command(company, department)
{
    _depName = department->name();
    _name = name;
    _surname = surname;
    _middleName = middleName;
    _function = function;
    _salary = salary;
    _id = name + surname + middleName + function;
}

void CmdAddEmployee::execute()
{

    _department = _company->departments()->value(_depName);
    if(!_department->employees()->count(_id))
    {
        _employee = _department->addEmployee(_name, _surname, _middleName, _function, _salary);
    }
}

void CmdAddEmployee::undo()
{
    if(_department->employees()->count(_id))
    {
        _department->removeEmployee(_id);
    }
}

