#ifndef STANDARD_USER_H
#define STANDARD_USER_H
#include <QString>
#include "user.h"
#include <QApplication>

class Standard_user : public User
{
public:
    Standard_user();
    virtual ~Standard_user() {}
    virtual void Acquista(Scontrino&, const int&punti=0);
};

#endif // STANDARD_USER_H
