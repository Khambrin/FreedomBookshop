#include "dvd.h"

DVD::DVD(const int &codice, const double &prezzo, const QString &titolo, const QString &regista, const QString &formato, const QString &audio, const QString &lingua, const QString &sottotitoli, const QDate &data_uscita, const int &durata):Item(codice, prezzo), Titolo(titolo), Regista(regista), Formato(formato), Audio(audio), Lingua(lingua), Sottotitoli(sottotitoli), Data_uscita(data_uscita), Durata(durata)
{

}

QString DVD::GetNome() const
{
    return Titolo;
}

QString DVD::GetRegista() const
{
    return Regista;
}

QString DVD::GetFormato() const
{
    return Formato;
}

QString DVD::GetAudio() const
{
    return Audio;
}

QString DVD::GetLingua() const
{
    return Lingua;
}

QString DVD::GetSottotitoli() const
{
    return Sottotitoli;
}

QDate DVD::GetData_uscita() const
{
    return Data_uscita;
}

int DVD::GetDurata() const
{
    return Durata;
}

