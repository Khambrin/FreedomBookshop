#include "databaseview.h"
#include <QString>
#include <QWidget>
#include <QFile>
#include <QIODevice>
#include <QFileDialog>

DatabaseView::DatabaseView()
{
    QString path=QDir::currentPath();
    path.append("/Database.xml");
    QFile database(path);
    if(!database.exists()){
        filename = QFileDialog::getSaveFileName((QWidget* )0,"Crea database Xml", ".","Xml files (*.xml)");
    }
    else {
        filename = QFileDialog::getOpenFileName((QWidget* )0,"Carica database Xml", ".","Xml files (*.xml)");
    }
}

DatabaseView::~DatabaseView()
{}

QString DatabaseView::GetFilename()
{
    return filename;
}

