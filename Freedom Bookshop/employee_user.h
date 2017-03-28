#ifndef EMPLOYEE_USER_H
#define EMPLOYEE_USER_H
#include "scontrino.h"
#include "premium_user.h"

class Employee_user : public Premium_user
{
public:
    Employee_user(const QString&, const QString&, const QString&, const QString&, const QString&, const int&);
    virtual ~Employee_user() {}
    virtual void Acquista(Scontrino&, const int&);
};

#endif // EMPLOYEE_USER_H
