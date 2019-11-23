#ifndef CMDADDDEPARTMENT_H
#define CMDADDDEPARTMENT_H

#include "command.h"
#include "company.h"

#include <QString>

class CmdAddDepartment : public Command
{

private:
    QString _departmentName;
    QString _newName;

public:
    CmdAddDepartment(Company *company, QString name);

    void execute();
    void undo();
};

#endif // CMDADDDEPARTMENT_H
