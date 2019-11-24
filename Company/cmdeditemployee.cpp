#include "cmdeditemployee.h"

CmdEditEmployee::CmdEditEmployee(Company* company, Department * dep, Employee * emp,
                                 QString newName,QString newSurname, QString newMiddleName,QString newFunction, int newSalary)
    :Command(company, dep, emp)
{
    _depName = dep->name();

    _name = emp->name();
    _surname = emp->surname();
    _middleName = emp->middleName();
    _function = emp->function();
    _salary = emp->salary();
    _id = emp->id();

    _newName = newName;
    _newSurname = newSurname;
    _newMiddleName= newMiddleName;
    _newFunction = newFunction;
    _newSalary = newSalary;
    _newId = newName + newSurname + newMiddleName + newFunction;
}

void CmdEditEmployee::undo()
{
    _department = _company->departments()->value(_depName);
    _employee = _department->employees()->value(_newId);

    if(_employee)
    _department->editEmployee(_newId, _name, _surname, _middleName,_function,_salary);
}

void CmdEditEmployee::execute()
{
    _department = _company->departments()->value(_depName);
    _employee = _department->employees()->value(_id);

    if(_employee)
    _department->editEmployee(_id , _newName, _newSurname, _newMiddleName, _newFunction, _newSalary);

}
