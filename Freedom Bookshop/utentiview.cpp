#include "utentiview.h"
#include "userlist.h"
#include <QTableWidget>
#include "premium_user.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>

UtentiView::UtentiView(QWidget* parent, Controller* control) : QWidget(parent), controller(control)
{
    connect(controller, SIGNAL(UsersChanged()), this, SLOT(RedrawUsers()));
    signalMapper = new QSignalMapper(this);
    Splitter= new QSplitter(this);
    QVBoxLayout* MainLayout= new QVBoxLayout(this);
    MainLayout->addWidget(Splitter);
    CreateLeftWidget();
    CreateRightWidget();
}

void UtentiView::CreateLeftWidget()
{
    Userlist* Utenti=controller->GetUtenti();
    Userlist::UserlistIterator it;
    TabellaUtenti= new QTableWidget(Utenti->size(), 7);
    int row=0;
    for(it=Utenti->begin();it!=Utenti->end();it++) {
        Premium_user* user=dynamic_cast<Premium_user*>(*it);
        if(user){
            int col=0;
            QTableWidgetItem* codice_carta = new QTableWidgetItem(user->GetCodice_carta());
            TabellaUtenti->setItem(row,col,codice_carta);
            ++col;
            QTableWidgetItem* e_mail = new QTableWidgetItem(user->GetE_mail());
            TabellaUtenti->setItem(row,col,e_mail);
            ++col;
            QTableWidgetItem* nome = new QTableWidgetItem(user->GetNome());
            TabellaUtenti->setItem(row,col,nome);
            ++col;
            QTableWidgetItem* cognome = new QTableWidgetItem(user->GetCognome());
            TabellaUtenti->setItem(row,col,cognome);
            ++col;
            QTableWidgetItem* telefono = new QTableWidgetItem(user->GetTelefono());
            TabellaUtenti->setItem(row,col,telefono);
            ++col;
            QTableWidgetItem* punti = new QTableWidgetItem(QString::number(user->GetPunti()));
            TabellaUtenti->setItem(row,col,punti);
            ++col;
            QPushButton* Remove_User = new QPushButton("Rimuovi utente", TabellaUtenti);
            TabellaUtenti->setCellWidget(row,col,Remove_User);
            QString codice=user->GetCodice_carta();
            connect(Remove_User, SIGNAL(clicked(bool)), signalMapper, SLOT(map()),Qt::UniqueConnection);
            signalMapper->setMapping(Remove_User,codice);
            connect(signalMapper, SIGNAL(mapped(const QString&)), this, SLOT(RequestRemoveUser(QString)),Qt::UniqueConnection);
            ++row;
        }
    }
    QStringList UtentiHeader;
    UtentiHeader << "Codice carta" << "E_mail" << "Nome" << "Cognome" << "Telefono" << "Punti" << "Rimuovi";
    TabellaUtenti->setHorizontalHeaderLabels(UtentiHeader);
    TabellaUtenti->setEditTriggers(QAbstractItemView::NoEditTriggers);
    Splitter->addWidget(TabellaUtenti);
}

void UtentiView::CreateRightWidget()
{
    QFormLayout* FormLayout= new QFormLayout();
    RightWidget = new QWidget;
    QLabel* Titolo = new QLabel("Aggiungi Utente");
    Codice= new QLineEdit(RightWidget);
    E_mail= new QLineEdit(RightWidget);
    Nome= new QLineEdit(RightWidget);
    Cognome= new QLineEdit(RightWidget);
    Telefono= new QLineEdit(RightWidget);
    Punti= new QLineEdit(RightWidget);
    QPushButton* Aggiungi_utente= new QPushButton("Aggiungi utente");
    Premium=new QRadioButton("Utente premium",RightWidget);
    Premium->setAutoExclusive(true);
    Employee=new QRadioButton("Utente impiegato",RightWidget);
    Employee->setAutoExclusive(true);
    FormLayout->addRow(Titolo);
    FormLayout->addRow("Codice",Codice);
    FormLayout->addRow("E_mail",E_mail);
    FormLayout->addRow("Nome",Nome);
    FormLayout->addRow("Cognome",Cognome);
    FormLayout->addRow("Telefono",Telefono);
    FormLayout->addRow("Punti",Punti);
    FormLayout->addRow(Premium);
    FormLayout->addRow(Employee);
    FormLayout->addRow(Aggiungi_utente);
    connect(Aggiungi_utente, SIGNAL(clicked(bool)),this, SLOT(RequestAddUser()),Qt::UniqueConnection);
    FormLayout->setSpacing(15);
    RightWidget->setLayout(FormLayout);
    Splitter->addWidget(RightWidget);
}

void UtentiView::RequestAddUser()
{
    QStringList Lista_Valori;
    Lista_Valori << Codice->text() << E_mail->text() << Nome->text() << Cognome->text() << Telefono->text() << Punti->text();
    if(Premium->isChecked()){
        Lista_Valori << "Premium";
    } else if(Employee->isChecked()) {
        Lista_Valori << "Employee";
    }
    controller->AddUtente(Lista_Valori);
}

void UtentiView::RequestRemoveUser(QString codice)
{
    controller->DeleteUtente(codice);
}

void UtentiView::RedrawUsers()
{
    delete TabellaUtenti;
    delete RightWidget;
    CreateLeftWidget();
    CreateRightWidget();
}



