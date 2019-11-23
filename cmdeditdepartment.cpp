#include "cmdeditdepartment.h"

CmdEditDepartment::CmdEditDepartment(Company * company , Department * dep, QString newName):Command(company,dep)
{
    _name = dep->name();
    _newName = newName;
}

void CmdEditDepartment::execute()
{
    _department = _company->departments()->value(_name);
    _department->setName(_newName);

    if(_department)
    {
        _company->departments()->remove(_name);
    }
    _company->departments()->insert(_newName, _department);
}

void CmdEditDepartment::undo()
{
    _department = _company->departments()->value(_newName);

    if(_department)
    {
        _company->departments()->remove(_newName);
    }
    _department->setName(_name);
    _company->departments()->insert(_name, _department);

}
