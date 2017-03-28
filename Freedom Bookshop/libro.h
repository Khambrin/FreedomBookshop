#ifndef LIBRO_H
#define LIBRO_H
#include "item.h"
#include <QString>
#include <QDate>

class Libro : public Item
{
private:
    QString Titolo;
    QString Autore;
    QString Lingua;
    QString Editore;
    QDate Data_pubblicazione;
    QString ISBN;
public:
    Libro(const int&,const double&, const QString&, const QString&, const QString&, const QString&, const QDate&, const QString&);
    virtual ~Libro() {}
    virtual QString GetNome() const;
    QString GetAutore() const;
    QString GetLingua() const;
    QString GetEditore() const;
    QDate GetData_pubblicazione() const;
    QString GetISBN() const;
};

#endif // LIBRO_H
