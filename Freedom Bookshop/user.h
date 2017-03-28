#ifndef USER_H
#define USER_H
#include <QString>
#include "scontrino.h"

class Scontrino;
class User
{
public:
    User();
    virtual ~User() {}
    virtual void Acquista(Scontrino&, const int&punti=0) = 0;
};

#endif // USER_H
