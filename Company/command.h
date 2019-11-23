#ifndef COMMAND_H
#define COMMAND_H
#include "company.h"

class Command
{

public:
    Command(Company * company = nullptr, Department * department = nullptr, Employee* employee = nullptr);

    virtual void execute() = 0;
    virtual void undo() = 0;

    virtual ~Command();

protected:
    Company * _company;
    Department * _department;
    Employee* _employee;
};

#endif // COMMAND_H
