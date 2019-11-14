#ifndef Company_H
#define Company_H

#include "subdivision.h"

#include <QObject>
#include <QFile>
#include <QtXml>
#include <QStandardItemModel>


class Company : public QStandardItemModel
{
    Q_OBJECT
public:
    Company();
    Company(QString name, QString pathXML);

    void addSubdivision(QString name);

    int size() const;

    ~Company();

    QMap<QString, Subdivision *> *subdivisions() const;



public slots :
    void openCompany();
    void addEmployee(QString subName, QString name, QString surname, QString patronymic, QString position, int salary);
signals:
    void go(QString);

private:
    QMap<QString , Subdivision*> *_subdivisions;
    QDomDocument *_doc;
    QString _pathXML;
    QString _name;

};

#endif // COMAPNY_H
