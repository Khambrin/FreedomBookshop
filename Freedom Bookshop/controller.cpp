#include "controller.h"
#include "libro.h"
#include "QTableView"
#include "databaseview.h"
#include "premium_user.h"
#include "employee_user.h"
#include "dvd.h"
#include "errors.h"

Controller::Controller()
{
    DatabaseView* dv = new DatabaseView;
    model=new Database(dv->GetFilename());
    delete dv;
}

Controller::~Controller()
{
    delete model;
}

Userlist *Controller::GetUtenti()
{
    return model->GetUsers();
}

QVector<Item *> *Controller::GetOggetti()
{
    return model->GetItems();
}

Scontrino *Controller::GetScontrino()
{
    return model->GetScontrino();
}

int Controller::GetNumLibri()
{
    return model->GetNumLibri();
}

int Controller::GetNumDvd()
{
    return model->GetNumDVD();
}

void Controller::DeleteUtente(QString codice)
{
    model->GetUsers()->Remove_user(codice);
    emit UsersChanged();
}

void Controller::DeleteProdotto(int codice)
{
    QVector<Item*>* Oggetti= model->GetItems();
    QVector<Item*>::iterator is;
    for(is=Oggetti->begin(); is!=Oggetti->end(); is++){
        if((*is)->GetCodice()==codice) {
            model->GetScontrino()->RemoveArticolo(*is);
        }
    }
    QVector<Item*>::iterator it;
    QVector<Item*>* items = model->GetItems();
    it=items->begin();
    int i;
    while(it!=items->end()){
        if((*it)->GetCodice()==codice){
            DVD* dvd=dynamic_cast<DVD*>(*it);
            if(dvd) {
                i=1;
            } else {
                i=0;
            }
            items->erase(it);
        } else {
            ++it;
        }
    }
    if(i){
        emit DVDChanged();
        emit ScontrinoChanged();
    } else {
        emit LibriChanged();
        emit ScontrinoChanged();
    }
}

void Controller::AddUtente(QStringList lista) try
{
    QString codice = lista[0];
    Userlist::UserlistIterator it;
    Userlist* users = model->GetUsers();
    for (it = users->begin(); it != users->end(); ++it) {
        Premium_user* user=dynamic_cast<Premium_user*>(*it);
        if (user && (user->GetCodice_carta() == codice)) {
            throw Id_not_unique;
        }
    }
    int i=0;
    QString Codice_carta=lista[i];
    ++i;
    QString E_mail=lista[i];
    ++i;
    QString Nome=lista[i];
    ++i;
    QString Cognome=lista[i];
    ++i;
    QString Telefono=lista[i];
    ++i;
    int Punti=lista[i].toInt();
    ++i;
    if(i<lista.size()){
        if(lista[i]=="Premium"){
            User* utente=new Premium_user(Codice_carta,E_mail,Nome,Cognome,Telefono,Punti);
            model->GetUsers()->push_back(utente);
        } else if (lista[i]=="Employee"){
            User* utente=new Employee_user(Codice_carta,E_mail,Nome,Cognome,Telefono,Punti);
            model->GetUsers()->push_back(utente);
        }
        emit UsersChanged();
    } else {
        throw Option_not_selected;
    }
} catch(Errors e) {
    if (e == Missing_value)
        emit Alert("Manca il codice utente");
    if (e == Id_not_unique)
        emit Alert("Esiste gia' un utente con questo codice");
    if (e == Option_not_selected)
        emit Alert("Selezionare la tipologia di utente");
}


void Controller::AddProdotto(QStringList lista) try
{
    int i=0;
    QString codice = lista[1];
    QVector<Item*>::iterator it;
    QVector<Item*>* itemlist = model->GetItems();
    for (it = itemlist->begin(); it != itemlist->end(); ++it) {
        if ((*it)->GetCodice() == codice.toInt()) {
            throw Id_not_unique;
        }
    }
    if(lista[i]=="libro") {
        ++i;
        QString codice=lista[i];
        int Codice=codice.toInt();
        ++i;
        QString prezzo=lista[i];
        double Prezzo=prezzo.toDouble();
        ++i;
        QString Titolo=lista[i];
        ++i;
        QString Autore=lista[i];
        ++i;
        QString Lingua=lista[i];
        ++i;
        QString Editore=lista[i];
        ++i;
        QDate Data_pubblicazione=QDate::fromString(lista[i],"dd.MM.yyyy");
        ++i;
        QString ISBN=lista[i];
        Libro* libro= new Libro(Codice,Prezzo,Titolo,Autore,Lingua,Editore,Data_pubblicazione,ISBN);
        model->GetItems()->push_back(libro);
        emit LibriChanged();
    } else if (lista[i]=="dvd") {
        ++i;
        QString codice=lista[i];
        int Codice=codice.toInt();
        ++i;
        QString prezzo=lista[i];
        double Prezzo=prezzo.toDouble();
        ++i;
        QString Titolo=lista[i];
        ++i;
        QString Regista=lista[i];
        ++i;
        QString Formato=lista[i];
        ++i;
        QString Audio=lista[i];
        ++i;
        QString Lingua=lista[i];
        ++i;
        QString Sottotitoli=lista[i];
        ++i;
        QDate Data_uscita=QDate::fromString(lista[i],"dd.MM.yyyy");
        ++i;
        int Durata=lista[i].toInt();
        DVD* dvd= new DVD(Codice,Prezzo,Titolo,Regista,Formato,Audio,Lingua,Sottotitoli,Data_uscita,Durata);
        model->GetItems()->push_back(dvd);
        emit DVDChanged();
    }
} catch(Errors e) {
    if (e == Missing_value)
        emit Alert("Codice prodotto mancante o non numerico");
    if (e == Id_not_unique)
        emit Alert("Esiste gia' un prodotto con questo codice");
}

void Controller::FinalizzaAcquisto(QString codice, QString punti) try
{
    Userlist* Users = model->GetUsers();
    User* utente = NULL;
    if(codice!="") {
        Userlist::UserlistIterator it;
        for(it=Users->begin(); it!=Users->end(); it++){
            Premium_user* u = dynamic_cast<Premium_user*>(*it);
            if(u && (u->GetCodice_carta()==codice)){
                if(u->GetPunti()<punti.toInt()){
                    throw Not_enough_points;
                }
                utente=u;   
            }
        } if(utente==NULL) {
            throw Inexistent_user;
        }
    }
    if(!utente){
        utente = new Standard_user;
    }
    int Punti=punti.toInt();
    utente->Acquista(*(model->GetScontrino()), Punti);
    model->GetScontrino()->SetUtente(utente);
    emit UsersChanged();
    emit AcquistoFinalizzato();
} catch(Errors e) {
    if (e == Not_enough_points)
        emit Alert("L'utente selezionato non dispone di abbastanza punti");
    if (e == Inexistent_user)
        emit Alert("Il codice selezionato non appartiene a nessun utente");
}

void Controller::AggiungiScontrino(int codice)
{
    QVector<Item*>* Oggetti= model->GetItems();
    QVector<Item*>::iterator it;
    for(it=Oggetti->begin(); it!=Oggetti->end(); it++){
        if((*it)->GetCodice()==codice) {
            model->GetScontrino()->AddArticolo(*it);
        }
    }
    emit ScontrinoChanged();
}

void Controller::TogliScontrino(int codice)
{
    QVector<Item*>* Oggetti= model->GetItems();
    QVector<Item*>::iterator it;
    for(it=Oggetti->begin(); it!=Oggetti->end(); it++){
        if((*it)->GetCodice()==codice) {
            model->GetScontrino()->RemoveArticolo(*it);
        }
    }
    emit ScontrinoChanged();
}

void Controller::WipeScontrino()
{
    model->GetScontrino()->Wipe();
    emit ScontrinoChanged();
}
