#include "presenter.h"
#include "ui_presenter.h"

Presenter::Presenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Presenter)
{
    ui->setupUi(this);
}

Presenter::~Presenter()
{
    delete ui;
}
