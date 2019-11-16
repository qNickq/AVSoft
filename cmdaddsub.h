#ifndef CMDADDSUB_H
#define CMDADDSUB_H

#include "command.h"
#include "company.h"

#include <QString>

class CmdAddSub : public Command
{

private:
    Company * _company;
    QString _subdivisionName;

public:
    CmdAddSub(Company *company, QString name);
    void execute();
};

#endif // CMDADDSUB_H
