#include "company.h"

Company::Company() : QStandardItemModel()
{
    QStringList list;
    list << "Отдел" << "Должность" << "Зарплата";
    setHorizontalHeaderLabels(list);

    _departments = new QMap<QString , Department*>();
}

QMap<QString, Department *> *Company::departments() const
{
    return _departments;
}

Department* Company::addDepartment(QString name)
{
    Department * department = new Department(name);

    _departments->insert(name, department);

    this->appendRow(department);
    return  department;
}

void Company::removeDepartment(QString name)
{
    int row = _departments->value(name)->row();
    this->removeRow(row);
    _departments->remove(name);
}

int Company::size() const
{
    return _departments->size();
}

Company::~Company()
{
    QMapIterator<QString, Department*> it (*departments());

    while(it.hasNext())
    {
        removeDepartment(it.next().key());
    }
    _departments->clear();
    delete _departments;
}
