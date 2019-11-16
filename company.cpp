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


void Company::addSubdivision(QString name)
{

    Subdivision * subdivision = new Subdivision(name);
    _subdivisions->insert(name, subdivision);
    this->appendRow(subdivision);

/*

*/

}

    /*/*****Update XML File*****
    QFile xmlFile(_pathXML + '/' + _name + ".xml");

    if (!xmlFile.open(QIODevice::ReadOnly)) return;

    if(!_doc->setContent(&xmlFile))
    {
        xmlFile.close();
        return;
    }
    xmlFile.close();

    QDomElement employee = _doc->createElement("employee");
    employee.setAttribute("surname", surname);
    employee.setAttribute("name", name);
    employee.setAttribute("patronymic", patronymic);
    employee.setAttribute("position", position);
    employee.setAttribute("salary", salary);

    QDomElement root = _doc->firstChildElement("company");
    QDomElement elt = root.firstChildElement("subdivision");

    for (; !elt.isNull(); elt = elt.nextSiblingElement("subdivision"))
    {
        if(elt.attribute("name") == _subdivisions->value(subName)->name())
        {
            elt.setAttribute("avg_salary", s->avgSalary());
            elt.setAttribute("count_employees", s->countEmp());
            elt.appendChild(employee);
            break;
        }
    }

    xmlFile.open(QIODevice::WriteOnly);
    xmlFile.write(_doc->toByteArray());
    xmlFile.close();
*/



int Company::size() const
{
    return _subdivisions->size();
}

Company::~Company()
{

}
