#ifndef PRESENTER_H
#define PRESENTER_H

#include "controller.h"

#include <QWidget>

namespace Ui {
class Presenter;
}

class Presenter : public QWidget
{
    Q_OBJECT
    
public:
    explicit Presenter(QWidget *parent = 0);
    ~Presenter();
    
private slots:
    void OnOpen();
    void OnPredict();
    void OnCellClicked(int i, int j);

private:
    Ui::Presenter *mp_ui;

    Controller m_controller;
};

#endif // PRESENTER_H
