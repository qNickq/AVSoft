#ifndef CMDEDITEMPLOYEE_H
#define CMDEDITEMPLOYEE_H

#include "command.h"
#include "company.h"

class CmdEditEmployee : public Command
{
public:
    CmdEditEmployee(Company* company, Department * dep, Employee * emp,
                    QString newName,QString newSurname, QString newMiddlename,QString newFunction, int newSalary);

    void undo();
    void execute();

private:
    QString _depName;
    QString _name;
    QString _surname;
    QString _middleName;
    QString _function;
    int _salary;
    QString _id;

    QString _newName;
    QString _newSurname;
    QString _newMiddleName;
    QString _newFunction;
    QString _newId;
    int _newSalary;
};

#endif // CMDEDITEMPLOYEE_H
