#ifndef CMDADDEMPLOYEE_H
#define CMDADDEMPLOYEE_H

#include "command.h"
#include "subdivision.h"

class CmdAddEmployee : public Command
{
private:
    Subdivision * _subdivision;

    QString _name;
    QString _surname;
    QString _patronymic;
    QString _position;

    int _salary;

public:
    CmdAddEmployee(Subdivision * subdivision ,QString name,QString surname, QString patronymic, QString position , int salary);

    void execute();

    ~CmdAddEmployee() ;
};

#endif // CMDADDEMPLOYEE_H
