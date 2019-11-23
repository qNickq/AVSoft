#ifndef CMDREMOVEDEPARTMENT_H
#define CMDREMOVEDEPARTMENT_H

#include "command.h"
#include "company.h"

#include <QString>

class CmdRemoveDepartment : public Command
{
private:
    QString _departmentName;
    QMap<QString, Employee> _employees;

public:
    CmdRemoveDepartment(Company *company, Department* department);

    void undo() override;
    void execute() override;
};

#endif // CMDREMOVEDEPARTMENT_H
