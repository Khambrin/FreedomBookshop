#ifndef ACQUISTIVIEW_H
#define ACQUISTIVIEW_H

#include <QWidget>
#include "scontrino.h"
#include "controller.h"
#include <QSignalMapper>
#include <QTableWidget>
#include <QRadioButton>
#include <QLineEdit>
#include <QStackedLayout>

class AcquistiView : public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    QSignalMapper* signalMapper;
    QVBoxLayout* MainLayout;
    QHBoxLayout* TopLayout;
    QStackedLayout* StackedLayout;
    QTableWidget* TabellaProdotti;
    QTableWidget* TabellaScontrino;
    QWidget* FirstPage;
    QWidget* SecondPage;
    QLineEdit* CodiceAggiungi;
    QLineEdit* CodiceTogli;
    QLineEdit* Punti;
    QLineEdit* Codice;
    void Createfirstpage();
    void Createsecondpage();
    void CreateProdottiTable();
    void CreateScontrinoTable();
public:
    explicit AcquistiView(QWidget *parent, Controller*);

signals:
    void ScontrinoChanged();
    void UsersChanged();
public slots:
    void ChangeIndex();
    void RedrawScontrino();
    void Acquista();
    void RequestAggiungiScontrino();
    void RequestTogliScontrino();
    void StampaScontrino();
};

#endif // ACQUISTIVIEW_H
