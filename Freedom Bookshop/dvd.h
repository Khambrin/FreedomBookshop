#ifndef DVD_H
#define DVD_H
#include "item.h"
#include <QString>
#include <QDate>

class DVD : public Item
{
private:
    QString Titolo;
    QString Regista;
    QString Formato;
    QString Audio;
    QString Lingua;
    QString Sottotitoli;
    QDate Data_uscita;
    int Durata;
public:
    DVD(const int&,const double&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QDate&, const int&);
    virtual ~DVD() {}
    virtual QString GetNome() const;
    QString GetRegista() const;
    QString GetFormato() const;
    QString GetAudio() const;
    QString GetLingua() const;
    QString GetSottotitoli() const;
    QDate GetData_uscita() const;
    int GetDurata() const;
};

#endif // DVD_H
