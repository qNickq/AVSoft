#include "cmdremovedepartment.h"

CmdRemoveDepartment::CmdRemoveDepartment(Company *company, Department *department):Command(company, department)
{
    _departmentName = department->name();

    QMap<QString, Employee*> map(*_department->employees());

    QMapIterator<QString, Employee*> i(map);

    while (i.hasNext())
    {
        i.next();
        _employees.insert(i.key(), *i.value());
    }
}

void CmdRemoveDepartment::undo()
{
    if(!_company->departments()->count(_departmentName))
    {
        _department = _company->addDepartment(_departmentName);

        QMapIterator<QString, Employee> i(_employees);

        while (i.hasNext())
        {
            i.next();
            Employee e = i.value();
            _department->addEmployee(e.name(), e.surname(),e.middleName(), e.function(),e.salary());
        }
    }

}

void CmdRemoveDepartment::execute()
{
    if(_company->departments()->count(_departmentName))
    {
        _company->removeDepartment(_departmentName);
    }
}
