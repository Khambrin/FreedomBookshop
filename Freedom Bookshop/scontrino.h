#ifndef SCONTRINO_H
#define SCONTRINO_H
#include "item.h"
#include <QVector>
#include <QString>
#include "user.h"

class User;
class Scontrino
{
private:
    QVector<const Item*>* Prodotti;
    int NumArticoli;
    int Prezzo_totale;
    int Sconto;
    int Prezzo_finale;
    User* Utente;
public:
    Scontrino(const int& = 0, const int& = 0, const int& = 0);
    void Print();
    void AddArticolo(const Item*);
    void RemoveArticolo(const Item *articolo);
    void SetSconto(const double&);
    QVector<const Item*>* GetProdotti() const;
    int GetNumArticoli() const;
    int GetPrezzo_totale() const;
    int GetPrezzo_finale() const;
    int GetPunti_guadagnati() const;
    int GetSconto() const;
    void Wipe();
    User* GetUtente() const;
    void SetUtente(User*);
};

#endif // SCONTRINO_H
