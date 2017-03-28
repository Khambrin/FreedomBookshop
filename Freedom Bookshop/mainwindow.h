#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QTabWidget>
#include <QTextEdit>
#include "controller.h"
#include <QMainWindow>
#include <QTableWidget>
#include "prodottiview.h"
#include "acquistiview.h"
#include "utentiview.h"

class UtentiView;
class MainWindow: public QMainWindow
{
    Q_OBJECT
private:
    Controller* controller;
    QTabWidget* TabWidget;
    QWidget* prodottiview;
    QWidget* utentiview;
    QWidget* acquistiview;
    void CreateProdottiView();
    void CreateTabWidget();
    void CreateUtentiView();
    void CreateAcquistiView();
signals:
public slots:
    void Alert(QString);
public:
    Controller* GetController();
    MainWindow(QWidget*, Controller*);
    ~MainWindow();
};

#endif // MAINWINDOW
