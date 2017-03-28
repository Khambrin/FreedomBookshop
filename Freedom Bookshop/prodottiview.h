#ifndef PRODOTTIVIEW_H
#define PRODOTTIVIEW_H

#include <QWidget>
#include <QTableWidget>
#include "controller.h"
#include <QSplitter>
#include <QSignalMapper>
#include <QRadioButton>
#include <QTableWidget>
#include <QVBoxLayout>

class ProdottiView : public QWidget
{
    Q_OBJECT
public:
    explicit ProdottiView(QWidget* parent, Controller*);
private:
    Controller* controller;
    QSignalMapper* signalMapperLibri;
    QSignalMapper* signalMapperDVD;
    QVBoxLayout* MainLayout;
    QTabWidget* Tabwidget;
    QWidget* Libri_widget;
    QWidget* DVD_widget;
    QWidget* LeftWidgetLibri;
    QWidget* RightWidgetLibri;
    QSplitter* SplitterLibri;
    QLineEdit* Codice_libro;
    QLineEdit* Prezzo_libro;
    QLineEdit* Titolo_libro;
    QLineEdit* Autore;
    QLineEdit* Lingua_libro;
    QLineEdit* Editore;
    QLineEdit* Data_pubblicazione;
    QLineEdit* ISBN;
    QWidget* RightWidgetDVD;
    QWidget* LeftWidgetDVD;
    QSplitter* SplitterDVD;
    QLineEdit* Codice_dvd;
    QLineEdit* Prezzo_dvd;
    QLineEdit* Titolo_dvd;
    QLineEdit* Regista;
    QLineEdit* Formato;
    QLineEdit* Audio;
    QLineEdit* Lingua_dvd;
    QLineEdit* Sottotitoli;
    QLineEdit* Data_uscita;
    QLineEdit* Durata;
    void CreateLeftWidgetLibri();
    void CreateRightWidgetLibri();
    void CreateLeftWidgetDVD();
    void CreateRightWidgetDVD();
signals:
    void RequestNewItem(QStringList);
public slots:
    void RequestRemoveItem(int);
    void RequestAddLibro();
    void RequestAddDVD();
    void RedrawLibri();
    void RedrawDVD();
};

#endif // PRODOTTIVIEW_H
