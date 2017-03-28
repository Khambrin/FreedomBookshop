#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QDialog>
#include "database.h"
#include "scontrino.h"

class Controller:public QDialog
{
    Q_OBJECT
private:
    Database* model;
public:
    Controller();
    ~Controller();
    Userlist* GetUtenti();
    QVector<Item*>* GetOggetti();
    Scontrino* GetScontrino();
    int GetNumLibri();
    int GetNumDvd();
    void DeleteUtente(QString);
    void DeleteProdotto(int);
    void AddUtente(QStringList);
    void AddProdotto(QStringList);
    void FinalizzaAcquisto(QString, QString);
    void AggiungiScontrino(int);
    void TogliScontrino(int);
    void WipeScontrino();
signals:
    void UsersChanged();
    void DVDChanged();
    void LibriChanged();
    void Alert(QString);
    void ScontrinoChanged();
    void AcquistoFinalizzato();
};

#endif // CONTROLLER_H
