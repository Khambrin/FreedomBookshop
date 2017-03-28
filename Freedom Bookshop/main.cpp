#include <QApplication>
#include "controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller* controller= new Controller;
    MainWindow* window= new MainWindow(NULL, controller);
    return a.exec();
}
