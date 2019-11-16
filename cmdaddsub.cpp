#include "cmdaddsub.h"

CmdAddSub::CmdAddSub(Company *company, QString name) : Command()
{
    _company = company;
    _subdivisionName = name;
}

void CmdAddSub::execute()
{
    _company->addSubdivision(_subdivisionName);
}
