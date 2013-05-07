 #include "presenter.h"
#include "ui_presenter.h"

#include <QFileDialog>

Presenter::Presenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Presenter)
{
    ui->setupUi(this);

    connect(ui->buttonOpen, SIGNAL(clicked()), this, SLOT(OnOpen()));
    connect(ui->buttonPredict, SIGNAL(clicked()), this, SLOT(OnPredict()));
}

Presenter::~Presenter()
{
    delete ui;
}

void Presenter::OnOpen()
{
    QDir dir = QFileDialog::getExistingDirectory(this, "Choose directory with CSV files");
    controller.Initialize(dir);
}

void Presenter::OnPredict()
{
    ui->editPrediction->setText(QString::number(controller.Forecast(ui->spinCompanyNumber->value())));
}
