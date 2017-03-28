#include "employee_user.h"

Employee_user::Employee_user(const QString &codice_carta, const QString &e_mail, const QString &nome, const QString &cognome, const QString &telefono, const int &punti):Premium_user(codice_carta, e_mail, nome, cognome, telefono, punti) {}

void Employee_user::Acquista(Scontrino &scontrino, const int &punt)
{
    this->Premium_user::Acquista(scontrino, punt);
    double sconto_employee=((scontrino.GetPrezzo_totale()*20)/100);
    scontrino.SetSconto(sconto_employee);
}
