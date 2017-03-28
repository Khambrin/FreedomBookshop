#include "acquistiview.h"
#include <QStackedLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include "standard_user.h"
#include "userlist.h"
#include "premium_user.h"
#include "employee_user.h"

AcquistiView::AcquistiView(QWidget *parent, Controller* control) : QWidget(parent), controller(control)
{
    connect(controller, SIGNAL(ScontrinoChanged()), this, SLOT(RedrawScontrino()));
    connect(controller, SIGNAL(LibriChanged()), this, SLOT(RedrawScontrino()));
    connect(controller, SIGNAL(DVDChanged()), this, SLOT(RedrawScontrino()));
    connect(controller, SIGNAL(AcquistoFinalizzato()), this, SLOT(StampaScontrino()));
    signalMapper = new QSignalMapper(this);
    StackedLayout= new QStackedLayout();
    Createfirstpage();
    StackedLayout->addWidget(FirstPage);
    MainLayout= new QVBoxLayout(this);
    MainLayout->addLayout(StackedLayout);
    this->setLayout(MainLayout);
}

void AcquistiView::ChangeIndex()
{
    StackedLayout->setCurrentIndex(0);
    StackedLayout->removeWidget(SecondPage);
}

void AcquistiView::RedrawScontrino()
{
    CreateScontrinoTable();
    StackedLayout->removeWidget(FirstPage);
    Createfirstpage();
    StackedLayout->addWidget(FirstPage);
}

void AcquistiView::Acquista()
{
    controller->FinalizzaAcquisto(Codice->text(), Punti->text());
}

void AcquistiView::StampaScontrino()
{
    Createsecondpage();
}

void AcquistiView::RequestAggiungiScontrino()
{
    controller->AggiungiScontrino(CodiceAggiungi->text().toInt());
}

void AcquistiView::RequestTogliScontrino()
{
    controller->TogliScontrino(CodiceTogli->text().toInt());
}

void AcquistiView::Createfirstpage()
{
    FirstPage= new QWidget;
    QVBoxLayout* FirstPageLayout= new QVBoxLayout();
    TopLayout= new QHBoxLayout();
    TopLayout->setSpacing(20);
    TopLayout->setMargin(20);
    CreateProdottiTable();
    TopLayout->addWidget(TabellaProdotti);
    QVBoxLayout* MiddleLayout= new QVBoxLayout();
    QLabel* CodiceAggiungiLabel = new QLabel("Codice prodotto");
    CodiceAggiungi= new QLineEdit();
    QPushButton* Aggiungi_prodotto= new QPushButton("Aggiungi prodotto");
    connect(Aggiungi_prodotto, SIGNAL(clicked(bool)), this, SLOT(RequestAggiungiScontrino()));
    QLabel* CodiceTogliLabel = new QLabel("Codice prodotto");
    CodiceTogli= new QLineEdit();
    QPushButton* Rimuovi_prodotto= new QPushButton("Rimuovi prodotto");
    connect(Rimuovi_prodotto, SIGNAL(clicked(bool)), this, SLOT(RequestTogliScontrino()));
    MiddleLayout->addWidget(CodiceAggiungiLabel);
    MiddleLayout->addWidget(CodiceAggiungi);
    MiddleLayout->addWidget(Aggiungi_prodotto);
    MiddleLayout->addWidget(CodiceTogliLabel);
    MiddleLayout->addWidget(CodiceTogli);
    MiddleLayout->addWidget(Rimuovi_prodotto);
    TopLayout->addLayout(MiddleLayout);
    CreateScontrinoTable();
    TopLayout->addWidget(TabellaScontrino);
    QHBoxLayout* BottomLayout= new QHBoxLayout();
    Punti= new QLineEdit();
    QLabel* punti= new QLabel("Punti spesi");
    Codice= new QLineEdit();
    QLabel* codice= new QLabel("Codice utente");
    BottomLayout->addWidget(punti);
    BottomLayout->addWidget(Punti);
    BottomLayout->addWidget(codice);
    BottomLayout->addWidget(Codice);
    QPushButton* Acquista=new QPushButton("Acquista");
    connect(Acquista, SIGNAL(clicked(bool)), this, SLOT(Acquista()));
    FirstPageLayout->addLayout(TopLayout);
    FirstPageLayout->addLayout(BottomLayout);
    FirstPageLayout->addWidget(Acquista);
    FirstPage->setLayout(FirstPageLayout);
    CreateScontrinoTable();
}

void AcquistiView::Createsecondpage()
{
    SecondPage = new QWidget();
    QVBoxLayout* SecondPageLayout= new QVBoxLayout();
    QLabel* Titolo = new QLabel("LIBRERIA FREEDOM");
    Titolo->setAlignment(Qt::AlignCenter);
    QFont* Title = new QFont();
    Title->setBold(true);
    Title->setPixelSize(25);
    Titolo->setFont(*Title);
    QLabel* SottoTitolo= new QLabel("Scontrino non fiscale");
    SottoTitolo->setAlignment(Qt::AlignCenter);
    QFont* Subtitle = new QFont();
    Subtitle->setPixelSize(20);
    SottoTitolo->setFont(*Subtitle);
    SecondPageLayout->addWidget(Titolo);
    SecondPageLayout->addWidget(SottoTitolo);
    QHBoxLayout* TabellaLayout= new QHBoxLayout();
    QVector<const Item*>* Scontrino= controller->GetScontrino()->GetProdotti();
    QVector<const Item*>::const_iterator it;
    QTableWidget* TabScontrino= new QTableWidget(Scontrino->size(), 2);
    int row=0;
    for(it=Scontrino->begin(); it!=Scontrino->end(); it++){
        int col=0;
        QTableWidgetItem* nome = new QTableWidgetItem((*it)->GetNome());
        TabScontrino->setItem(row,col,nome);
        ++col;
        QTableWidgetItem* prezzo = new QTableWidgetItem(QString::number((*it)->GetPrezzo()));
        TabScontrino->setItem(row,col,prezzo);
        ++row;
    }
    QStringList ScontrinoHeader;
    ScontrinoHeader << "Nome" << "Prezzo";
    TabScontrino->setHorizontalHeaderLabels(ScontrinoHeader);
    TabScontrino->setEditTriggers(QAbstractItemView::NoEditTriggers);
    TabScontrino->horizontalHeader()->setStretchLastSection(true);
    TabellaLayout->addStretch();
    TabellaLayout->addWidget(TabScontrino);
    TabellaLayout->addStretch();
    SecondPageLayout->addLayout(TabellaLayout);
    QString totale= "Totale = ";
    totale.append(QString::number(controller->GetScontrino()->GetPrezzo_totale()));
    QLabel* Totale= new QLabel(totale);
    Totale->setAlignment(Qt::AlignCenter);
    QFont* Total = new QFont();
    Total->setPixelSize(15);
    Totale->setFont(*Total);
    SecondPageLayout->addWidget(Totale);
    Premium_user* utente=dynamic_cast<Premium_user*>(controller->GetScontrino()->GetUtente());
    if(utente) {
        QString punti= "Punti guadagnati = ";
        punti.append(QString::number(controller->GetScontrino()->GetPunti_guadagnati()));
        QLabel* Punti= new QLabel(punti);
        Punti->setAlignment(Qt::AlignCenter);
        QFont* Points = new QFont();
        Points->setPixelSize(12);
        Punti->setFont(*Points);
        QString sconto= "Sconto = ";
        sconto.append(QString::number(controller->GetScontrino()->GetSconto()));
        QLabel* Sconto= new QLabel(sconto);
        Sconto->setAlignment(Qt::AlignCenter);
        QFont* Discount = new QFont();
        Discount->setPixelSize(12);
        Sconto->setFont(*Discount);
        QString finale= "Prezzo finale = ";
        finale.append(QString::number(controller->GetScontrino()->GetPrezzo_finale()));
        QLabel* Finale= new QLabel(finale);
        Finale->setAlignment(Qt::AlignCenter);
        QFont* Final = new QFont();
        Final->setPixelSize(15);
        Finale->setFont(*Final);
        SecondPageLayout->addWidget(Punti);
        SecondPageLayout->addWidget(Sconto);
        SecondPageLayout->addWidget(Finale);
    }
    controller->WipeScontrino();
    QPushButton* TornaIndietro= new QPushButton("Torna indietro");
    connect(TornaIndietro, SIGNAL(clicked(bool)), this, SLOT(ChangeIndex()));
    SecondPageLayout->addWidget(TornaIndietro);
    SecondPage->setLayout(SecondPageLayout);
    StackedLayout->addWidget(SecondPage);
    StackedLayout->setCurrentIndex(1);
}

void AcquistiView::CreateProdottiTable()
{
    QVector<Item*>* Oggetti=controller->GetOggetti();
    QVector<Item*>::iterator ip;
    TabellaProdotti= new QTableWidget(controller->GetOggetti()->size(), 2);
    int row=0;
    for(ip=Oggetti->begin(); ip!=Oggetti->end(); ip++){
        int col=0;
        QTableWidgetItem* codice = new QTableWidgetItem(QString::number((*ip)->GetCodice()));
        TabellaProdotti->setItem(row,col,codice);
        ++col;
        QTableWidgetItem* nome = new QTableWidgetItem((*ip)->GetNome());
        TabellaProdotti->setItem(row,col,nome);
        ++col;
        QTableWidgetItem* prezzo = new QTableWidgetItem((*ip)->GetPrezzo());
        TabellaProdotti->setItem(row,col,prezzo);
        ++row;
    }
    QStringList ProdottiHeader;
    ProdottiHeader << "Codice" << "Nome" << "Prezzo";
    TabellaProdotti->setHorizontalHeaderLabels(ProdottiHeader);
    TabellaProdotti->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void AcquistiView::CreateScontrinoTable()
{
    QVector<const Item*>* Scontrino= controller->GetScontrino()->GetProdotti();
    QVector<const Item*>::const_iterator it;
    TabellaScontrino= new QTableWidget(Scontrino->size(), 2);
    int row=0;
    for(it=Scontrino->begin(); it!=Scontrino->end(); it++){
        int col=0;
        QTableWidgetItem* codice = new QTableWidgetItem(QString::number((*it)->GetCodice()));
        TabellaScontrino->setItem(row,col,codice);
        ++col;
        QTableWidgetItem* nome = new QTableWidgetItem((*it)->GetNome());
        TabellaScontrino->setItem(row,col,nome);
        ++col;
        QTableWidgetItem* prezzo = new QTableWidgetItem((*it)->GetPrezzo());
        TabellaScontrino->setItem(row,col,prezzo);
        ++row;
    }
    QStringList ScontrinoHeader;
    ScontrinoHeader << "Codice" << "Nome" << "Prezzo";
    TabellaScontrino->setHorizontalHeaderLabels(ScontrinoHeader);
    TabellaScontrino->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

