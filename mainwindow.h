#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QtGui>
#include <QDeclarativeContext>
#include <QFileDialog>

#include "modelitem.h"
#include "modelcompany.h"
#include "model.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Q_INVOKABLE void FunctionC();//Функция C++ вызываемая из QML
private:
    void _FormModel();

    QDeclarativeView *mp_ui;
    QObject *mp_root;
    Model m_model;
};

#endif // MAINWINDOW_H
