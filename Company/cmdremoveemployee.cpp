#include "cmdremoveemployee.h"

CmdRemoveEmployee::CmdRemoveEmployee(Company * company,Department* department, Employee *employee)
    :Command(company, department, employee)
{

 _depName = _department->name();

 _name = employee->name();
 _surname = employee->surname();
 _middleName = employee->middleName();
 _function = employee->function();
 _salary = employee->salary();
 _id = _employee->id();

}

void CmdRemoveEmployee::execute()
{
    _department = _company->departments()->value(_depName);
    _department->removeEmployee(_id);
}

void CmdRemoveEmployee::undo()
{
    _department = _company->departments()->value(_depName);

    if(!_department->employees()->count(_id))
    {
        _department->addEmployee(_name,_surname,_middleName,_function,_salary);
    }
}
