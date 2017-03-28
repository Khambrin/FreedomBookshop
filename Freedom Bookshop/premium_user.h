#ifndef PREMIUM_USER_H
#define PREMIUM_USER_H
#include "standard_user.h"

class Premium_user : public Standard_user
{
private:
    QString Codice_carta;
    QString E_mail;
    QString Nome;
    QString Cognome;
    QString Telefono;
    int Punti;
public:
    Premium_user(const QString&, const QString&, const QString&, const QString&, const QString&, const int&);
    virtual ~Premium_user() {}
    virtual void Acquista(Scontrino&, const int &punti=0);
    QString GetCodice_carta() const;
    QString GetE_mail() const;
    QString GetNome() const;
    QString GetCognome() const;
    QString GetTelefono() const;
    int GetPunti() const;
};
#endif // PREMIUM_USER_H
