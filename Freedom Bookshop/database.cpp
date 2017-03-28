#include "database.h"
#include "premium_user.h"
#include "employee_user.h"
#include "item.h"
#include "libro.h"
#include "dvd.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDate>

Database::Database(QString filepath):filename(filepath)
{
    Users=new Userlist;
    Items=new QVector<Item*>;
    scontrino= new Scontrino;
    QFile file(filename);
    file.open(QIODevice::ReadWrite);

    QXmlStreamReader  xml(&file);
    xml.readNext();
    while(!xml.atEnd()){
        if(xml.isStartElement()){
            if(xml.name()=="Database"){
                xml.readNext();
            } else if((xml.name()=="Items")|(xml.name()=="Users")) {
                xml.readNext();
            }
            if(xml.isStartElement()) {
                if(xml.name()=="Libro"){
                    xml.readNextStartElement();
                    int Codice=xml.readElementText().toInt();
                    xml.readNextStartElement();
                    double Prezzo=xml.readElementText().toDouble();
                    xml.readNextStartElement();
                    QString Titolo=xml.readElementText();
                    xml.readNextStartElement();
                    QString Autore=xml.readElementText();
                    xml.readNextStartElement();
                    QString Lingua=xml.readElementText();
                    xml.readNextStartElement();
                    QString Editore=xml.readElementText();
                    xml.readNextStartElement();
                    QDate Data_pubblicazione= QDate::fromString(xml.readElementText(),"dd.MM.yyyy");
                    xml.readNextStartElement();
                    QString ISBN=xml.readElementText();
                    xml.readNextStartElement();
                    Libro* libro= new Libro(Codice,Prezzo,Titolo,Autore,Lingua,Editore,Data_pubblicazione,ISBN);
                    Items->push_back(libro);
                } else if(xml.name()=="DVD"){
                    xml.readNextStartElement();
                    int Codice=xml.readElementText().toInt();
                    xml.readNextStartElement();
                    double Prezzo=xml.readElementText().toDouble();
                    xml.readNextStartElement();
                    QString Titolo=xml.readElementText();
                    xml.readNextStartElement();
                    QString Regista=xml.readElementText();
                    xml.readNextStartElement();
                    QString Formato=xml.readElementText();
                    xml.readNextStartElement();
                    QString Audio=xml.readElementText();
                    xml.readNextStartElement();
                    QString Lingua=xml.readElementText();
                    xml.readNextStartElement();
                    QString Sottotitoli=xml.readElementText();
                    xml.readNextStartElement();
                    QDate Data_uscita= QDate::fromString(xml.readElementText(),"dd.MM.yyyy");
                    xml.readNextStartElement();
                    int Durata=xml.readElementText().toInt();
                    xml.readNextStartElement();
                    DVD* dvd= new DVD(Codice,Prezzo,Titolo,Regista,Formato,Audio,Lingua,Sottotitoli,Data_uscita,Durata);
                    Items->push_back(dvd);
                } else if(xml.name()=="Premium_user") {
                    xml.readNextStartElement();
                    QString Codice_carta=xml.readElementText();
                    xml.readNextStartElement();
                    QString E_mail=xml.readElementText();
                    xml.readNextStartElement();
                    QString Nome=xml.readElementText();
                    xml.readNextStartElement();
                    QString Cognome=xml.readElementText();
                    xml.readNextStartElement();
                    QString Telefono=xml.readElementText();
                    xml.readNextStartElement();
                    int Punti=xml.readElementText().toInt();
                    xml.readNextStartElement();
                    Premium_user* premium_user= new Premium_user(Codice_carta,E_mail,Nome,Cognome,Telefono,Punti);
                    Users->push_back(premium_user);
                } else if(xml.name()=="Employee_user") {
                    xml.readNextStartElement();
                    QString Codice_carta=xml.readElementText();
                    xml.readNextStartElement();
                    QString E_mail=xml.readElementText();
                    xml.readNextStartElement();
                    QString Nome=xml.readElementText();
                    xml.readNextStartElement();
                    QString Cognome=xml.readElementText();
                    xml.readNextStartElement();
                    QString Telefono=xml.readElementText();
                    xml.readNextStartElement();
                    int Punti=xml.readElementText().toInt();
                    xml.readNextStartElement();
                    Employee_user* employee_user= new Employee_user(Codice_carta,E_mail,Nome,Cognome,Telefono,Punti);
                    Users->push_back(employee_user);
                }
            }
        }
        xml.readNext();
    }
    file.close();
}

Database::~Database()
{
    this->SaveDB();
    delete Items;
    delete Users;
    delete scontrino;
}

void Database::SaveDB()
{
    QFile file(filename);
    /*QString Codice_carta("codice");
    QString E_mail("email");
    QString Nome("nome");
    QString Cognome("cognome");
    QString Telefono("telefono");
    int Punti(5);
    QString Codice_carta2("codice2");
    QString E_mail2("email2");
    QString Nome2("nome2");
    QString Cognome2("cognome2");
    QString Telefono2("telefono2");
    int Punti2(95);
    Premium_user* prov=new Premium_user(Codice_carta,E_mail,Nome,Cognome,Telefono,Punti);
    Employee_user* ener=new Employee_user(Codice_carta2,E_mail2,Nome2,Cognome2,Telefono2,Punti2);
    Users->push_back(ener);
    Users->push_back(prov);*/
    /*int Codice(100);
    double Prezzo(9.76);
    QString Titolo("titolo");
    QString Autore("autore");
    QString Lingua("lingua");
    QString Editore("editore");
    QDate Data_pubblicazione(2011,07,11);
    QString ISBN("isbn");
    Libro* l=new Libro(Codice,Prezzo,Titolo,Autore,Lingua,Editore,Data_pubblicazione,ISBN);
    Items.push_back(l);
    QString Regista("regista");
    QString Formato("formato");
    QString Audio("audio");
    QString Sottotitoli("sottotitoli");
    QDate Data_uscita(2045,11,20);
    int Durata(8);
    DVD* d=new DVD(Codice,Prezzo,Titolo,Regista,Formato,Lingua,Audio,Sottotitoli,Data_uscita,Durata);
    Items.push_back(d);*/
    QString path=filename;
    QFile database(path);
    if(!database.exists()){
        filename = QFileDialog::getSaveFileName((QWidget* )0,"Crea database Xml in cui salvare i dati", ".","Xml files (*.xml)");
    }
    file.open(QIODevice::ReadWrite);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Database");
    xmlWriter.writeStartElement("Users");

    Userlist::UserlistIterator it;
    for(it=Users->begin(); it!=Users->end(); it++) {
        Employee_user* e=dynamic_cast<Employee_user*>(*it);
        if(e){
            xmlWriter.writeStartElement("Employee_user");
            xmlWriter.writeTextElement("Codice_carta", e->GetCodice_carta());
            xmlWriter.writeTextElement("E_mail", e->GetE_mail());
            xmlWriter.writeTextElement("Nome", e->GetNome());
            xmlWriter.writeTextElement("Cognome", e->GetCognome());
            xmlWriter.writeTextElement("Telefono", e->GetTelefono());
            xmlWriter.writeTextElement("Punti", QString::number(e->GetPunti()));
            xmlWriter.writeEndElement();
        } else {
            Premium_user* p=dynamic_cast<Premium_user*>(*it);
            if(p){
                xmlWriter.writeStartElement("Premium_user");
                xmlWriter.writeTextElement("Codice_carta", p->GetCodice_carta());
                xmlWriter.writeTextElement("E_mail", p->GetE_mail());
                xmlWriter.writeTextElement("Nome", p->GetNome());
                xmlWriter.writeTextElement("Cognome", p->GetCognome());
                xmlWriter.writeTextElement("Telefono", p->GetTelefono());
                xmlWriter.writeTextElement("Punti", QString::number(p->GetPunti()));
                xmlWriter.writeEndElement();
            }
        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("Items");
    QVector<Item*>::Iterator b;
    for(b=Items->begin(); b!=Items->end(); b++) {
        Libro* l=dynamic_cast<Libro*>(*b);
        if(l){
            xmlWriter.writeStartElement("Libro");
            xmlWriter.writeTextElement("Codice",QString::number(l->GetCodice()));
            xmlWriter.writeTextElement("Prezzo", QString::number(l->GetPrezzo()));
            xmlWriter.writeTextElement("Titolo", l->GetNome());
            xmlWriter.writeTextElement("Autore", l->GetAutore());
            xmlWriter.writeTextElement("Lingua", l->GetLingua());
            xmlWriter.writeTextElement("Editore", l->GetEditore());
            xmlWriter.writeTextElement("Data_pubblicazione",l->GetData_pubblicazione().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("ISBN", l->GetISBN());
            xmlWriter.writeEndElement();
        }
        DVD* d=dynamic_cast<DVD*>(*b);
        if(d){
            xmlWriter.writeStartElement("DVD");
            xmlWriter.writeTextElement("Codice",QString::number(d->GetCodice()));
            xmlWriter.writeTextElement("Prezzo", QString::number(d->GetPrezzo()));
            xmlWriter.writeTextElement("Titolo", d->GetNome());
            xmlWriter.writeTextElement("Regista", d->GetRegista());
            xmlWriter.writeTextElement("Formato", d->GetFormato());
            xmlWriter.writeTextElement("Audio", d->GetAudio());
            xmlWriter.writeTextElement("Lingua", d->GetLingua());
            xmlWriter.writeTextElement("Sottotitoli", d->GetSottotitoli());
            xmlWriter.writeTextElement("Data_uscita", d->GetData_uscita().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("Durata", QString::number(d->GetDurata()));
            xmlWriter.writeEndElement();

        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

}
/*
void Database::insert(const User *)
{
    QString path=filename;
    QFile database(path);
    if(!database.exists()){
        filename = QFileDialog::getSaveFileName((QWidget* )0,"Crea database Xml", ".","Xml files (*.xml)");
    }
    else {
        filename = QFileDialog::getOpenFileName((QWidget* )0,"Carica database Xml", ".","Xml files (*.xml)");
    }
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Database");
    xmlWriter.writeStartElement("Users");

    Userlist::UserlistIterator i;
    for(i=Users.begin(); i!=Users.end(); i++) {
        Premium_user* p=dynamic_cast<Premium_user*>(*i);
        if(p){
            xmlWriter.writeStartElement("Premium_user");
            xmlWriter.writeTextElement("Codice_carta", p->GetCodice_carta());
            xmlWriter.writeTextElement("E_mail", p->GetE_mail());
            xmlWriter.writeTextElement("Nome", p->GetNome());
            xmlWriter.writeTextElement("Cognome", p->GetCognome());
            xmlWriter.writeTextElement("Telefono", p->GetTelefono());
            xmlWriter.writeTextElement("Punti", QString::number(p->GetPunti()));
            xmlWriter.writeEndElement();
        }
        Employee_user* e=dynamic_cast<Employee_user*>(*i);
        if(e){
            xmlWriter.writeStartElement("Employee_user");
            xmlWriter.writeTextElement("Codice_carta", p->GetCodice_carta());
            xmlWriter.writeTextElement("E_mail", p->GetE_mail());
            xmlWriter.writeTextElement("Nome", p->GetNome());
            xmlWriter.writeTextElement("Cognome", p->GetCognome());
            xmlWriter.writeTextElement("Telefono", p->GetTelefono());
            xmlWriter.writeTextElement("Punti", QString::number(p->GetPunti()));
            xmlWriter.writeEndElement();

        }
    }
    QVector<Item*>::Iterator it;
    it=Items.begin();
    for(it=Items.begin(); it!=Items.end(); it++) {
        Libro* l=dynamic_cast<Libro*>(*it);
        if(l){
            xmlWriter.writeStartElement("Libro");
            xmlWriter.writeTextElement("Codice",QString::number(l->GetCodice()));
            xmlWriter.writeTextElement("Prezzo", QString::number(l->GetPrezzo()));
            xmlWriter.writeTextElement("Titolo", l->GetNome());
            xmlWriter.writeTextElement("Autore", l->GetAutore());
            xmlWriter.writeTextElement("Lingua", l->GetLingua());
            xmlWriter.writeTextElement("Editore", l->GetEditore());
            xmlWriter.writeTextElement("Data_pubblicazione",l->GetData_pubblicazione().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("ISBN", l->GetISBN());
            xmlWriter.writeEndElement();
        }
        DVD* d=dynamic_cast<DVD*>(*it);
        if(d){
            xmlWriter.writeStartElement("DVD");
            xmlWriter.writeTextElement("Codice",QString::number(d->GetCodice()));
            xmlWriter.writeTextElement("Prezzo", QString::number(d->GetPrezzo()));
            xmlWriter.writeTextElement("Titolo", d->GetNome());
            xmlWriter.writeTextElement("Regista", d->GetRegista());
            xmlWriter.writeTextElement("Formato", d->GetFormato());
            xmlWriter.writeTextElement("Audio", d->GetAudio());
            xmlWriter.writeTextElement("Lingua", d->GetLingua());
            xmlWriter.writeTextElement("Sottotitoli", d->GetSottotitoli());
            xmlWriter.writeTextElement("Data_uscita", d->GetData_uscita().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("Durata", QString::number(d->GetDurata()));
            xmlWriter.writeEndElement();

        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

void Database::insert(const Item *)
{
    QString path=filename;
    QFile database(path);
    if(!database.exists()){
        filename = QFileDialog::getSaveFileName((QWidget* )0,"Crea database Xml", ".","Xml files (*.xml)");
    }
    else {
        filename = QFileDialog::getOpenFileName((QWidget* )0,"Carica database Xml", ".","Xml files (*.xml)");
    }
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Database");
    xmlWriter.writeStartElement("Users");

    QVector<Item*>::Iterator it;
    for(it=Items->begin(); it!=Items.end(); it++) {
        Libro* l=dynamic_cast<Libro*>(*it);
        if(l){
            xmlWriter.writeStartElement("Libro");
            xmlWriter.writeTextElement("Codice",QString::number(l->GetCodice()));
            xmlWriter.writeTextElement("Prezzo", QString::number(l->GetPrezzo()));
            xmlWriter.writeTextElement("Titolo", l->GetNome());
            xmlWriter.writeTextElement("Autore", l->GetAutore());
            xmlWriter.writeTextElement("Lingua", l->GetLingua());
            xmlWriter.writeTextElement("Editore", l->GetEditore());
            xmlWriter.writeTextElement("Data_pubblicazione",l->GetData_pubblicazione().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("ISBN", l->GetISBN());
            xmlWriter.writeEndElement();
        }
        DVD* d=dynamic_cast<DVD*>(*it);
        if(d){
            xmlWriter.writeStartElement("DVD");
            xmlWriter.writeTextElement("Codice",QString::number(d->GetCodice()));
            xmlWriter.writeTextElement("Prezzo", QString::number(d->GetPrezzo()));
            xmlWriter.writeTextElement("Titolo", d->GetNome());
            xmlWriter.writeTextElement("Regista", d->GetRegista());
            xmlWriter.writeTextElement("Formato", d->GetFormato());
            xmlWriter.writeTextElement("Audio", d->GetAudio());
            xmlWriter.writeTextElement("Lingua", d->GetLingua());
            xmlWriter.writeTextElement("Sottotitoli", d->GetSottotitoli());
            xmlWriter.writeTextElement("Data_uscita", d->GetData_uscita().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("Durata", QString::number(d->GetDurata()));
            xmlWriter.writeEndElement();

        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}*/

QVector<Item*>* Database::GetItems()
{
    return Items;
}

Userlist* Database::GetUsers()
{
    return Users;
}

Scontrino *Database::GetScontrino()
{
    return scontrino;
}

int Database::GetNumLibri()
{
    int num=0;
    QVector<Item*>::iterator it;
    for(it=Items->begin(); it!=Items->end(); it++) {
        Libro* l=dynamic_cast<Libro*>(*it);
        if(l){
            num++;
        }
    }
    return num;

}

int Database::GetNumDVD()
{
    int num=0;
    QVector<Item*>::iterator it;
    for(it=Items->begin(); it!=Items->end(); it++) {
        DVD* d=dynamic_cast<DVD*>(*it);
        if(d){
            num++;
        }
    }
    return num;

}
