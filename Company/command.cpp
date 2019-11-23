#include "command.h"

Command::Command(Company *company, Department *department, Employee* employee) :
    _company(company), _department(department), _employee(employee)
{

}

Command::~Command()
{

}
