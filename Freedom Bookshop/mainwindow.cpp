#include <QGroupBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QMessageBox>
#include "controller.h"
#include "mainwindow.h"
#include "user.h"
#include "premium_user.h"
#include <iostream>
#include "utentiview.h"
#include "acquistiview.h"

MainWindow::MainWindow(QWidget*, Controller* control)
{
    controller=control;
    CreateProdottiView();
    CreateUtentiView();
    CreateAcquistiView();
    CreateTabWidget();
    this->setCentralWidget(TabWidget);
    this->show();
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(controller, SIGNAL(Alert(QString)), this, SLOT(Alert(QString)));
}

MainWindow::~MainWindow()
{
    delete controller;
    delete prodottiview;
    delete utentiview;
    delete acquistiview;
}

void MainWindow::CreateProdottiView()
{
    prodottiview= new ProdottiView(NULL, controller);
}

void MainWindow::CreateTabWidget()
{
    setMinimumSize( 800, 480 );
    TabWidget = new QTabWidget(this);
    TabWidget->addTab(prodottiview,"Prodotti");
    TabWidget->addTab(utentiview, "Utenti");
    TabWidget->addTab(acquistiview, "Acquisti");
    TabWidget->show();
}

void MainWindow::CreateUtentiView()
{
    utentiview = new UtentiView(NULL, controller);
}

void MainWindow::CreateAcquistiView()
{
    acquistiview= new AcquistiView(NULL, controller);
}

void MainWindow::Alert(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

Controller *MainWindow::GetController()
{
    return controller;
}
