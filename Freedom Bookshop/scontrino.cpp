#include "scontrino.h"

Scontrino::Scontrino(const int &numarticoli, const int &prezzo_totale, const int &sconto):NumArticoli(numarticoli), Prezzo_totale(prezzo_totale), Sconto(sconto), Prezzo_finale(prezzo_totale)
{
    Prodotti= new QVector<const Item*>;
}

void Scontrino::AddArticolo(const Item* articolo)
{
    Prodotti->push_back(articolo);
    double prezzo_articolo=articolo->GetPrezzo();
    Prezzo_totale=Prezzo_totale+prezzo_articolo;
    Prezzo_finale=Prezzo_totale;
    NumArticoli++;
}

void Scontrino::RemoveArticolo(const Item* articolo)
{
    int it=Prodotti->lastIndexOf(articolo);
    if(it!=-1) {
        Prodotti->remove(it);
        double prezzo_articolo=articolo->GetPrezzo();
        Prezzo_totale=Prezzo_totale-prezzo_articolo;
        Prezzo_finale=Prezzo_totale;
        NumArticoli--;
    }
}

void Scontrino::SetSconto(const double &sconto)
{
    Sconto=Sconto+sconto;
    Prezzo_finale=Prezzo_totale-Sconto;
}

QVector<const Item *>* Scontrino::GetProdotti() const
{
    return Prodotti;
}

int Scontrino::GetNumArticoli() const
{
    return NumArticoli;
}

int Scontrino::GetPrezzo_totale() const
{
    return Prezzo_totale;
}

int Scontrino::GetPrezzo_finale() const
{
    return Prezzo_finale;
}

int Scontrino::GetPunti_guadagnati() const
{
    int punti_guadagnati=((this->GetPrezzo_totale())/10);
    return punti_guadagnati;
}

int Scontrino::GetSconto() const
{
    return Sconto;
}

void Scontrino::Wipe()
{
    Prodotti->erase(Prodotti->begin(),Prodotti->end());
    NumArticoli=0;
    Prezzo_totale=0;
    Prezzo_finale=0;
    Sconto=0;
    Utente=NULL;
}

User* Scontrino::GetUtente() const
{
    return Utente;
}

void Scontrino::SetUtente(User *value)
{
    Utente = value;
}
