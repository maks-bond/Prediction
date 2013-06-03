#include "presenter.h"
#include "ui_presenter.h"
#include "datamodel.h"

#include <QFileDialog>
#include <QMessageBox>

Presenter::Presenter(QWidget *parent) :
    QWidget(parent),
    mp_ui(new Ui::Presenter)
{
    mp_ui->setupUi(this);
    setWindowTitle("GMDH Forecaster");
    connect(mp_ui->buttonOpen, SIGNAL(clicked()), this, SLOT(OnOpen()));
    connect(mp_ui->buttonPredict, SIGNAL(clicked()), this, SLOT(OnPredict()));
    connect(mp_ui->tableData, SIGNAL(cellClicked(int,int)), this, SLOT(OnCellClicked(int, int)));
}

Presenter::~Presenter()
{
    delete mp_ui;
}

void Presenter::OnOpen()
{
    QDir dir = QFileDialog::getExistingDirectory(this, "Choose directory with CSV files");
    m_controller.Initialize(dir);
    const Matrix& curData = m_controller.GetDataModel()->GetRawData();
    int cols = curData.GetVariablesNumber();
    int rows = curData.GetObservationNumber();
    mp_ui->tableData->setColumnCount(cols);
    mp_ui->tableData->setRowCount(rows);

    mp_ui->tableData->setHorizontalHeaderLabels(m_controller.GetDataModel()->GetCompaniesNames().toList());

    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            mp_ui->tableData->setItem(j,i,new QTableWidgetItem(tr("%1").arg(curData.GetObservation(i,j))));
        }
    }
}

void Presenter::OnPredict()
{
    if(!m_controller.IsValidCompanyName(mp_ui->editCompanyName))
    {
        QMessageBox::critical(this, "Error", "You must set correct company name!");
        return;
    }
    //ui->editPrediction->setText(QString::number(controller.Forecast(ui->spinCompanyNumber->value())));
}

void Presenter::OnCellClicked(int i, int j)
{
    QString text = mp_ui->tableData->horizontalHeaderItem(j)->text();
    mp_ui->editCompanyName->setText(mp_ui->tableData->horizontalHeaderItem(j)->text());
}
