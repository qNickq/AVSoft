#ifndef Company_H
#define Company_H

#include <QObject>
#include <QStandardItemModel>

#include "subdivision.h"

class Company : public QStandardItemModel
{
    Q_OBJECT
public:

    Company(QString name);

    void addSubdivision(QString name);

    int size() const;

    ~Company();

    QMap<QString, Subdivision *> *subdivisions() const;

private:
    QMap<QString , Subdivision*> *_subdivisions;
    QString _name;
};

#endif // COMAPNY_H
