#include "prodottiview.h"
#include <QVector>
#include <QTableWidget>
#include "libro.h"
#include "dvd.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>

ProdottiView::ProdottiView(QWidget *parent, Controller *control) : QWidget(parent), controller(control)
{
    connect(controller, SIGNAL(LibriChanged()), this, SLOT(RedrawLibri()));
    connect(controller, SIGNAL(DVDChanged()), this, SLOT(RedrawDVD()));
    SplitterLibri= new QSplitter(this);
    SplitterDVD= new QSplitter(this);
    signalMapperLibri = new QSignalMapper(this);
    signalMapperDVD = new QSignalMapper(this);
    CreateLeftWidgetLibri();
    CreateRightWidgetLibri();
    CreateLeftWidgetDVD();
    CreateRightWidgetDVD();
    QVBoxLayout* LibriLayout = new QVBoxLayout();
    LibriLayout->addWidget(SplitterLibri);
    QVBoxLayout* DVDLayout = new QVBoxLayout();
    DVDLayout->addWidget(SplitterDVD);
    Libri_widget = new QWidget;
    Libri_widget->setLayout(LibriLayout);
    DVD_widget = new QWidget;
    DVD_widget->setLayout(DVDLayout);
    setMinimumSize( 800, 480 );
    Tabwidget = new QTabWidget(this);
    Tabwidget->addTab(Libri_widget, "Libri");
    Tabwidget->addTab(DVD_widget, "DVD");
    MainLayout = new QVBoxLayout(this);
    MainLayout->addWidget(Tabwidget);
}

void ProdottiView::CreateLeftWidgetLibri()
{
    QVector<Item*>* Oggetti=controller->GetOggetti();
    QVector<Item*>::iterator il;
    QTableWidget* TabellaLibri= new QTableWidget(controller->GetNumLibri(), 9);
    int row=0;
    for(il=Oggetti->begin(); il!=Oggetti->end(); il++){
        Libro* libro=dynamic_cast<Libro*>(*il);
        if(libro){
            int col=0;
            QTableWidgetItem* codice = new QTableWidgetItem(QString::number(libro->GetCodice()));
            TabellaLibri->setItem(row,col,codice);
            ++col;
            QTableWidgetItem* prezzo = new QTableWidgetItem(QString::number(libro->GetPrezzo()));
            TabellaLibri->setItem(row,col,prezzo);
            ++col;
            QTableWidgetItem* titolo = new QTableWidgetItem(libro->GetNome());
            TabellaLibri->setItem(row,col,titolo);
            ++col;
            QTableWidgetItem* autore = new QTableWidgetItem(libro->GetAutore());
            TabellaLibri->setItem(row,col,autore);
            ++col;
            QTableWidgetItem* lingua = new QTableWidgetItem(libro->GetLingua());
            TabellaLibri->setItem(row,col,lingua);
            ++col;
            QTableWidgetItem* editore = new QTableWidgetItem(libro->GetEditore());
            TabellaLibri->setItem(row,col,editore);
            ++col;
            QTableWidgetItem* data_pubblicazione = new QTableWidgetItem(libro->GetData_pubblicazione().toString("dd.MM.yyyy"));
            TabellaLibri->setItem(row,col,data_pubblicazione);
            ++col;
            QTableWidgetItem* isbn = new QTableWidgetItem(libro->GetISBN());
            TabellaLibri->setItem(row,col,isbn);
            ++col;
            QPushButton* Remove_Libro = new QPushButton("Rimuovi libro");
            TabellaLibri->setCellWidget(row,col,Remove_Libro);
            int codice_libro=libro->GetCodice();
            connect(Remove_Libro, SIGNAL(clicked(bool)), signalMapperLibri, SLOT(map()),Qt::UniqueConnection);
            signalMapperLibri->setMapping(Remove_Libro,codice_libro);
            connect(signalMapperLibri, SIGNAL(mapped(int)), this, SLOT(RequestRemoveItem(int)),Qt::UniqueConnection);
            ++row;
        }
    }
    QStringList LibriHeader;
    LibriHeader << "Codice" << "Prezzo" << "Titolo" << "Autore" << "Lingua" << "Editore" << "Data pubblicazione" << "ISBN" << "Rimuovi";
    TabellaLibri->setHorizontalHeaderLabels(LibriHeader);
    TabellaLibri->setEditTriggers(QAbstractItemView::NoEditTriggers);
    SplitterLibri->addWidget(TabellaLibri);
}

void ProdottiView::CreateRightWidgetLibri()
{
    QFormLayout* FormLayout= new QFormLayout();
    QLabel* Titolo = new QLabel("Aggiungi Libro");
    Codice_libro= new QLineEdit(this);
    Prezzo_libro= new QLineEdit(this);
    Titolo_libro= new QLineEdit(this);
    Autore= new QLineEdit(this);
    Lingua_libro= new QLineEdit(this);
    Editore= new QLineEdit(this);
    Data_pubblicazione= new QLineEdit(this);
    ISBN= new QLineEdit(this);
    QPushButton* Aggiungi_libro= new QPushButton("Aggiungi libro");
    FormLayout->addRow(Titolo);
    FormLayout->addRow("Codice",Codice_libro);
    FormLayout->addRow("Prezzo",Prezzo_libro);
    FormLayout->addRow("Titolo",Titolo_libro);
    FormLayout->addRow("Autore",Autore);
    FormLayout->addRow("Lingua",Lingua_libro);
    FormLayout->addRow("Editore",Editore);
    FormLayout->addRow("Data pubblicazione",Data_pubblicazione);
    FormLayout->addRow("ISBN",ISBN);
    FormLayout->addRow(Aggiungi_libro);
    connect(Aggiungi_libro, SIGNAL(clicked(bool)),this, SLOT(RequestAddLibro()),Qt::UniqueConnection);
    QWidget* RightWidget = new QWidget;
    FormLayout->setSpacing(15);
    RightWidget->setLayout(FormLayout);
    SplitterLibri->addWidget(RightWidget);
}

void ProdottiView::CreateLeftWidgetDVD()
{
    QVector<Item*>* Oggetti=controller->GetOggetti();
    QTableWidget* TabellaDVD= new QTableWidget(controller->GetNumDvd(), 11);
    QVector<Item*>::iterator id;
    int row=0;
    for(id=Oggetti->begin(); id!=Oggetti->end(); id++){
        DVD* dvd=dynamic_cast<DVD*>(*id);
        if(dvd){
            int col=0;
            QTableWidgetItem* codice = new QTableWidgetItem(QString::number(dvd->GetCodice()));
            TabellaDVD->setItem(row,col,codice);
            ++col;
            QTableWidgetItem* prezzo = new QTableWidgetItem(QString::number(dvd->GetPrezzo()));
            TabellaDVD->setItem(row,col,prezzo);
            ++col;
            QTableWidgetItem* titolo = new QTableWidgetItem(dvd->GetNome());
            TabellaDVD->setItem(row,col,titolo);
            ++col;
            QTableWidgetItem* regista = new QTableWidgetItem(dvd->GetRegista());
            TabellaDVD->setItem(row,col,regista);
            ++col;
            QTableWidgetItem* formato = new QTableWidgetItem(dvd->GetFormato());
            TabellaDVD->setItem(row,col,formato);
            ++col;
            QTableWidgetItem* audio = new QTableWidgetItem(dvd->GetAudio());
            TabellaDVD->setItem(row,col,audio);
            ++col;
            QTableWidgetItem* lingua = new QTableWidgetItem(dvd->GetLingua());
            TabellaDVD->setItem(row,col,lingua);
            ++col;
            QTableWidgetItem* sottotitoli = new QTableWidgetItem(dvd->GetSottotitoli());
            TabellaDVD->setItem(row,col,sottotitoli);
            ++col;
            QTableWidgetItem* data_uscita = new QTableWidgetItem(dvd->GetData_uscita().toString("dd.MM.yyyy"));
            TabellaDVD->setItem(row,col,data_uscita);
            ++col;
            QTableWidgetItem* durata = new QTableWidgetItem(QString::number(dvd->GetDurata()));
            TabellaDVD->setItem(row,col,durata);
            ++col;
            QPushButton* Remove_DVD = new QPushButton("Rimuovi dvd");
            TabellaDVD->setCellWidget(row,col,Remove_DVD);
            int codice_dvd=dvd->GetCodice();
            connect(Remove_DVD, SIGNAL(clicked(bool)), signalMapperDVD, SLOT(map()),Qt::UniqueConnection);
            signalMapperDVD->setMapping(Remove_DVD,codice_dvd);
            connect(signalMapperDVD, SIGNAL(mapped(int)), this, SLOT(RequestRemoveItem(int)),Qt::UniqueConnection);
            ++row;
        }
    }
    QStringList DVDHeader;
    DVDHeader << "Codice" << "Prezzo" << "Titolo" << "Regista" << "Formato" << "Audio" << "Lingua" << "Sottotitoli" << "Data uscita" << "Durata" << "Rimuovi";
    TabellaDVD->setHorizontalHeaderLabels(DVDHeader);
    TabellaDVD->setEditTriggers(QAbstractItemView::NoEditTriggers);
    SplitterDVD->addWidget(TabellaDVD);
}

void ProdottiView::CreateRightWidgetDVD()
{
    QFormLayout* FormLayout= new QFormLayout();
    QLabel* Titolo = new QLabel("Aggiungi DVD");
    Codice_dvd= new QLineEdit(this);
    Prezzo_dvd= new QLineEdit(this);
    Titolo_dvd= new QLineEdit(this);
    Regista= new QLineEdit(this);
    Formato= new QLineEdit(this);
    Audio= new QLineEdit(this);
    Lingua_dvd= new QLineEdit(this);
    Sottotitoli= new QLineEdit(this);
    Data_uscita= new QLineEdit(this);
    Durata= new QLineEdit(this);
    QPushButton* Aggiungi_dvd= new QPushButton("Aggiungi dvd");
    FormLayout->addRow(Titolo);
    FormLayout->addRow("Codice",Codice_dvd);
    FormLayout->addRow("Prezzo",Prezzo_dvd);
    FormLayout->addRow("Titolo",Titolo_dvd);
    FormLayout->addRow("Regista",Regista);
    FormLayout->addRow("Formato",Formato);
    FormLayout->addRow("Audio",Audio);
    FormLayout->addRow("Lingua",Lingua_dvd);
    FormLayout->addRow("Stottotitoli",Sottotitoli);
    FormLayout->addRow("Data uscita",Data_uscita);
    FormLayout->addRow("Durata",Durata);
    FormLayout->addRow(Aggiungi_dvd);
    connect(Aggiungi_dvd, SIGNAL(clicked(bool)),this, SLOT(RequestAddDVD()),Qt::UniqueConnection);
    QWidget* RightWidget = new QWidget;
    FormLayout->setSpacing(15);
    RightWidget->setLayout(FormLayout);
    SplitterDVD->addWidget(RightWidget);
}

void ProdottiView::RequestAddLibro()
{
    QStringList Lista_Valori;
    Lista_Valori << "libro" << Codice_libro->text() << Prezzo_libro->text() << Titolo_libro->text() << Autore->text() << Lingua_libro->text() << Editore->text() << Data_pubblicazione->text() << ISBN->text();
    controller->AddProdotto(Lista_Valori);
}

void ProdottiView::RequestAddDVD()
{
    QStringList Lista_Valori;
    Lista_Valori << "dvd" << Codice_dvd->text() << Prezzo_dvd->text() << Titolo_dvd->text() << Regista->text() << Formato->text() << Audio->text() << Lingua_dvd->text() << Sottotitoli->text() << Data_uscita->text() << Durata->text();
    controller->AddProdotto(Lista_Valori);
}

void ProdottiView::RedrawLibri()
{
    delete SplitterLibri;
    delete Libri_widget;
    SplitterLibri= new QSplitter(this);
    signalMapperLibri= new QSignalMapper(this);
    CreateLeftWidgetLibri();
    CreateRightWidgetLibri();
    QVBoxLayout* LibriLayout = new QVBoxLayout();
    LibriLayout->addWidget(SplitterLibri);
    Libri_widget = new QWidget;
    Libri_widget->setLayout(LibriLayout);
    MainLayout->removeWidget(Tabwidget);
    Tabwidget->removeTab(2);
    Tabwidget->removeTab(1);
    Tabwidget->addTab(Libri_widget, "Libri");
    Tabwidget->addTab(DVD_widget, "DVD");
    MainLayout->addWidget(Tabwidget);
    Tabwidget->setCurrentIndex(2);
}

void ProdottiView::RedrawDVD()
{
    delete SplitterDVD;
    delete DVD_widget;
    SplitterDVD= new QSplitter(this);
    signalMapperDVD= new QSignalMapper(this);
    CreateLeftWidgetDVD();
    CreateRightWidgetDVD();
    QVBoxLayout* DVDLayout = new QVBoxLayout();
    DVDLayout->addWidget(SplitterDVD);
    DVD_widget = new QWidget;
    DVD_widget->setLayout(DVDLayout);
    MainLayout->removeWidget(Tabwidget);
    Tabwidget->removeTab(2);
    Tabwidget->removeTab(1);
    Tabwidget->addTab(Libri_widget, "Libri");
    Tabwidget->addTab(DVD_widget, "DVD");
    MainLayout->addWidget(Tabwidget);
    Tabwidget->setCurrentIndex(1);
}

void ProdottiView::RequestRemoveItem(int codice)
{
    controller->DeleteProdotto(codice);
}
