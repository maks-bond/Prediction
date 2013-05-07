#include "mainwindow.h"
#include <QApplication>

#include "presenter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Presenter p;
    p.show();
    return a.exec();
}
