#ifndef CMDEDITDEPARTMENT_H
#define CMDEDITDEPARTMENT_H

#include "command.h"
#include "department.h"

class CmdEditDepartment : public Command
{
public:
    CmdEditDepartment(Company * company, Department* dep, QString newName);

    void execute() override;
    void undo() override;

private:
    QString _name;
    QString _newName;
};

#endif // CMDEDITDEPARTMENT_H
