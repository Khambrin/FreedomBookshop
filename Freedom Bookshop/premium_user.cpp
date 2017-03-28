#include "premium_user.h"
#include "errors.h"

Premium_user::Premium_user(const QString &codice_carta, const QString &e_mail, const QString &nome, const QString &cognome, const QString &telefono, const int &punti)
{
    if(codice_carta==NULL){
        throw Missing_value;
    }
    Codice_carta=codice_carta;
    E_mail=e_mail;
    Nome=nome;
    Cognome=cognome;
    Telefono=telefono;
    Punti=punti;
}

void Premium_user::Acquista(Scontrino &scontrino, const int &punt)
{
    double sconto=punt;
    scontrino.SetSconto(sconto);
    Punti=Punti-punt;
    int punti_guadagnati=((scontrino.GetPrezzo_totale())/10);
    Punti=Punti+punti_guadagnati;
}


QString Premium_user::GetCodice_carta() const
{
    return Codice_carta;
}

QString Premium_user::GetE_mail() const
{
    return E_mail;
}

QString Premium_user::GetNome() const
{
    return Nome;
}

QString Premium_user::GetCognome() const
{
    return Cognome;
}

QString Premium_user::GetTelefono() const
{
    return Telefono;
}

int Premium_user::GetPunti() const
{
    return Punti;
}

