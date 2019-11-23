#ifndef Company_H
#define Company_H

#include <QObject>
#include <QStandardItemModel>

#include "department.h"

class Company : public QStandardItemModel
{
    Q_OBJECT

private:
    QMap<QString , Department*> *_departments;

public:
    Company();

    Department *addDepartment(QString name);

    void removeDepartment(QString name);

    QMap<QString, Department *> *departments() const;
    int size() const;

    ~Company();



};

#endif // COMAPNY_H
