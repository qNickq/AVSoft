#include "company.h"

Company::Company()
{

}

Company::Company(QString name, QString path)
{

    _name = name;
    _pathXML = path;
    _subdivisions = new QMap<QString , Subdivision*>();
    _doc = new QDomDocument(name);

    QDomElement company = _doc->createElement("company");
    company.setAttribute("name", name);
    _doc->appendChild(company);

    QFile xmlFile(path + '/' + name + ".xml");
    xmlFile.open(QIODevice::WriteOnly);
    xmlFile.write(_doc->toByteArray());
    xmlFile.close();

}

void Company::openCompany()
{

}

QMap<QString, Subdivision *> *Company::subdivisions() const
{
    return _subdivisions;
}


void Company::addSubdivision(QString name)
{
    int countName = _subdivisions->count(name);

    if(countName != 0)
    {
        name += QString("%1").arg(countName);
    }
    emit go(name);
    Subdivision * subdivision = new Subdivision(name);
    _subdivisions->insert(name, subdivision);
    this->appendRow(subdivision);


    QFile xmlFile(_pathXML + '/' + _name + ".xml");

    if (!xmlFile.open(QIODevice::ReadOnly)) return;

    if(!_doc->setContent(&xmlFile))
    {
        xmlFile.close();
        return;
    }
    xmlFile.close();

    QDomElement sub = _doc->createElement("subdivision");

    sub.setAttribute("name", name);
    sub.setAttribute("count_employees", "0");
    sub.setAttribute("avg_salary", "0");

    _doc->documentElement().appendChild(sub);

    xmlFile.open(QIODevice::WriteOnly);
    xmlFile.write(_doc->toByteArray());
    xmlFile.close();

}

void Company::addEmployee(QString subName, QString name, QString surname, QString patronymic, QString position, int salary)
{

    Subdivision *s = _subdivisions->value(subName);
    s->addEmployee(name, surname, patronymic, position, salary);


    //*****Update XML File*****//
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
}

int Company::size() const
{
    return _subdivisions->size();
}


Company::~Company()
{

}
