#ifndef ITEM_H
#define ITEM_H
#include <QString>


class Item
{
private:
    int Codice;
    double Prezzo;
public:
    Item(const int&,const double& prezzo=0);
    virtual ~Item() {}
    int GetCodice() const;
    double GetPrezzo() const;
    virtual QString GetNome() const =0;
    //virtual void Save() const =0;
};

#endif // ITEM_H
