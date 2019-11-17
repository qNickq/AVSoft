#ifndef CMDADDSUB_H
#define CMDADDSUB_H

#include "command.h"
#include "company.h"

#include <QString>

class CmdAddSub : public Command
{

private:
    Company * _company;
    Subdivision * _subdivision;
    QString _subdivisionName;

public:
    CmdAddSub(Company *company, QString name);
    void execute();
    void undo();
    void redo();
};

#endif // CMDADDSUB_H
