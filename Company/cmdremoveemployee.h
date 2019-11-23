#ifndef CMDREMOVEEMPLOYEE_H
#define CMDREMOVEEMPLOYEE_H

#include "command.h"
#include "company.h"


class CmdRemoveEmployee : public Command
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
    CmdRemoveEmployee(Company * company, Department* department, Employee * employee);

    void execute();
    void undo();
};

#endif // CMDREMOVEEMPLOYEE_H
