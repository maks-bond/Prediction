#include "presenter.h"
#include "ui_presenter.h"
#include "datamodel.h"

#include <QFileDialog>

Presenter::Presenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Presenter)
{
    ui->setupUi(this);
    setWindowTitle("GMDH Forecaster");
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
    const Matrix& curData = controller.GetDataModel()->GetRawData();
    int cols = curData.GetVariablesNumber();
    int rows = curData.GetObservationNumber();
    ui->tableData->setColumnCount(cols);
    ui->tableData->setRowCount(rows);

    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            ui->tableData->setItem(j,i,new QTableWidgetItem(tr("%1").arg(curData.GetObservation(i,j))));
        }
    }
}

void Presenter::OnPredict()
{
    //ui->editPrediction->setText(QString::number(controller.Forecast(ui->spinCompanyNumber->value())));
}
