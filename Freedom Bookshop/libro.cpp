#include "libro.h"

Libro::Libro(const int &codice, const double &prezzo, const QString &titolo, const QString &autore, const QString &lingua, const QString &editore, const QDate &data_pubblicazione, const QString &isbn):Item(codice,prezzo), Titolo(titolo), Autore(autore), Lingua(lingua), Editore(editore), Data_pubblicazione(data_pubblicazione), ISBN(isbn) {}

QString Libro::GetNome() const
{
    return Titolo;
}

QString Libro::GetAutore() const
{
    return Autore;
}

QString Libro::GetLingua() const
{
    return Lingua;
}

QString Libro::GetEditore() const
{
    return Editore;
}

QDate Libro::GetData_pubblicazione() const
{
    return Data_pubblicazione;
}

QString Libro::GetISBN() const
{
    return ISBN;
}
