#include "company.h"

Company::Company(QString name)
{
    _name = name;
    _subdivisions = new QMap<QString , Subdivision*>();
}

QMap<QString, Subdivision *> *Company::subdivisions() const
{
    return _subdivisions;
}

Subdivision* Company::addSubdivision(QString name)
{
    Subdivision * subdivision = new Subdivision(name);
    _subdivisions->insert(name, subdivision);
    this->appendRow(subdivision);

    return  subdivision;
}

void Company::removeSubdivision(QString name)
{
    int row = _subdivisions->value(name)->row();
    this->removeRow(row);
    _subdivisions->remove(name);
}

int Company::size() const
{
    return _subdivisions->size();
}

Company::~Company()
{
    QMap<QString, Subdivision*>::iterator it = _subdivisions->begin();
    while(it != _subdivisions->end())
    {
        delete it.value();
        ++it;
    }
    _subdivisions->clear();
    delete _subdivisions;
}
