#ifndef CMDADDEMPLOYEE_H
#define CMDADDEMPLOYEE_H

#include "command.h"
#include "company.h"

class CmdAddEmployee : public Command
{
private:
    QString _depName;
    QString _name;
    QString _surname;
    QString _middleName;
    QString _function;
    QString _id;

    int _salary;

public:
    CmdAddEmployee(Company* company, Department* department,QString name,QString surname, QString middleName, QString function , int salary);

    void execute();
    void undo();
};

#endif // CMDADDEMPLOYEE_H
