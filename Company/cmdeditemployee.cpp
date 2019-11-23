#include "cmdeditemployee.h"

CmdEditEmployee::CmdEditEmployee(Company* company, Department * dep, Employee * emp,
                                 QString newName,QString newSurname, QString newMiddlename,QString newFunction, int newSalary)
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
    _newMiddleName= newMiddlename;
    _newFunction = newFunction;
    _newSalary = newSalary;
    _newId = newName + newSurname + newMiddlename + newFunction;

}

void CmdEditEmployee::undo()
{

    _department = _company->departments()->value(_depName);
    _employee = _department->employees()->value(_newId);

    if(_employee)
    {
        _department->employees()->remove(_newId);
    }
    _department->employees()->insert(_id, _employee);

    _employee->setName(_name);
    _employee->setSurname(_surname);
    _employee->setMiddleName(_middleName);
    _employee->setFunction(_function);
    _employee->setSalary(_salary);
    _employee->setId(_id);

    _employee->setData(_surname + ' ' + _name + ' ' + _middleName, Qt::DisplayRole);

}

void CmdEditEmployee::execute()
{
    _department = _company->departments()->value(_depName);

    _employee = _department->employees()->value(_id);

    if(_employee)
    {
        _department->employees()->remove(_id);
    }

    _department->employees()->insert(_newId, _employee);

    if(!_newName.isNull())
        _employee->setName(_newName);

    if(!_newSurname.isNull())
        _employee->setSurname(_newSurname);

    if(!_newMiddleName.isNull())
        _employee->setMiddleName(_newMiddleName);

    if(!_newFunction.isNull())
        _employee->setFunction(_newFunction);

    if(_newSalary != 0)
        _employee->setSalary(_newSalary);

    _employee->setId(_newId);

    _employee->setData(_newSurname + ' ' + _newName + ' ' + _newMiddleName, Qt::DisplayRole);
}
