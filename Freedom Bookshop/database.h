#ifndef DATABASE_H
#define DATABASE_H
#include <QFile>
#include <QIODevice>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "userlist.h"
#include <QVector>
#include <QFileDialog>
#include "scontrino.h"

class Database
{
private:
    Userlist* Users;
    QVector<Item*>* Items;
    Scontrino* scontrino;
    QString filename;
public:
    Database(QString);
    ~Database();
    void SaveDB();
    QVector<Item*>* GetItems();
    Userlist* GetUsers();
    Scontrino* GetScontrino();
    int GetNumLibri();
    int GetNumDVD();
};

#endif // DATABASE_H
