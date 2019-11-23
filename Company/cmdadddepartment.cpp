#include "cmdadddepartment.h"

CmdAddDepartment::CmdAddDepartment(Company *company, QString name) : Command()
{
    _company = company;
    _departmentName = name;
    _department = nullptr;
}

void CmdAddDepartment::execute()
{
    if(!_company->departments()->count(_departmentName))
    {
        _department = _company->addDepartment(_departmentName);
    }
}

void CmdAddDepartment::undo()
{
    if(_company->departments()->count(_departmentName))
    {
        _company->removeDepartment(_departmentName);
    }
}
