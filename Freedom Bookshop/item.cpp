#include "item.h"
#include "errors.h"

Item::Item(const int &codice, const double &prezzo)
{
    if(!codice) {
        throw Missing_value;
    }
    Codice=codice;
    Prezzo=prezzo;
}

int Item::GetCodice() const
{
    return Codice;
}

double Item::GetPrezzo() const
{
    return Prezzo;
}

