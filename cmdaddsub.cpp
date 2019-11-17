#include "cmdaddsub.h"

CmdAddSub::CmdAddSub(Company *company, QString name) : Command()
{
    _company = company;
    _subdivisionName = name;
    _subdivision = nullptr;
}

void CmdAddSub::execute()
{
    _subdivision = _company->addSubdivision(_subdivisionName);
}

void CmdAddSub::undo()
{
    _company->removeSubdivision(_subdivisionName);
}

void CmdAddSub::redo()
{
     _subdivision = _company->addSubdivision(_subdivisionName);
}
