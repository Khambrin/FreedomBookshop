#ifndef UTENTIVIEW_H
#define UTENTIVIEW_H

#include <QWidget>
#include <QTableWidget>
#include "controller.h"
#include <QSplitter>
#include <QSignalMapper>
#include <QRadioButton>

class UtentiView : public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    QWidget* RightWidget;
    QTableWidget* TabellaUtenti;
    QSplitter* Splitter;
    QSignalMapper* signalMapper;
    QLineEdit* Codice;
    QLineEdit* E_mail;
    QLineEdit* Nome;
    QLineEdit* Cognome;
    QLineEdit* Telefono;
    QLineEdit* Punti;
    QRadioButton* Premium;
    QRadioButton* Employee;
    void CreateLeftWidget();
    void CreateRightWidget();
public:
    explicit UtentiView(QWidget* parent, Controller*);
signals:
    void RequestNewUser(QStringList);
public slots:
    void RequestRemoveUser(QString);
    void RequestAddUser();
    void RedrawUsers();
};

#endif // UTENTIVIEW_H
