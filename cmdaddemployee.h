#ifndef CMDADDEMPLOYEE_H
#define CMDADDEMPLOYEE_H

#include "command.h"
#include "subdivision.h"
#include "company.h"
class CmdAddEmployee : public Command
{
private:
    Company* _company;
    Subdivision* _subdivision;
    Employee* _employee;

    QString _subname;
    QString _name;
    QString _surname;
    QString _patronymic;
    QString _position;

    int _salary;

public:
    CmdAddEmployee(Company* company, QString subname,QString name,QString surname, QString patronymic, QString position , int salary);

    void execute();
    void undo();
    void redo();
};

#endif // CMDADDEMPLOYEE_H
