#include "presenter.h"
#include "ui_presenter.h"
#include "datamodel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>

namespace
{
    QStringList _FormSequentialDates(const QDate& i_start_date, int i_date_count)
    {
        QStringList res;

        for(int i = 0; i<i_date_count; ++i)
            res.push_back(i_start_date.addDays(i).toString("dd.MM.yyyy"));

        return res;
    }
}

Presenter::Presenter(QWidget *parent) :
    QWidget(parent),
    mp_ui(new Ui::Presenter)
{
    mp_ui->setupUi(this);
    setWindowTitle("GMDH Forecaster");
    connect(mp_ui->buttonOpen, SIGNAL(clicked()), this, SLOT(OnOpen()));
    connect(mp_ui->buttonPredict, SIGNAL(clicked()), this, SLOT(OnPredict()));
    connect(mp_ui->tableData, SIGNAL(cellPressed(int,int)), this, SLOT(OnCellClicked(int, int)));
    connect(mp_ui->tableData, SIGNAL(cellActivated(int,int)), this, SLOT(OnCellClicked(int, int)));
    connect(mp_ui->tableData->verticalScrollBar(), SIGNAL(valueChanged(int)), mp_ui->tableResult->verticalScrollBar(), SLOT(setValue(int)));
    connect(mp_ui->tableResult->verticalScrollBar(), SIGNAL(valueChanged(int)), mp_ui->tableData->verticalScrollBar(), SLOT(setValue(int)));

    mp_ui->tableResult->setColumnCount(2);
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
    mp_ui->tableData->setVerticalHeaderLabels(_FormSequentialDates(m_controller.GetDataModel()->GetStartDate(), m_controller.GetDataModel()->GetObservationNumber()));

    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            mp_ui->tableData->setItem(j,i,new QTableWidgetItem(QString::number(curData.GetObservation(i,j))));
        }
    }
}

void Presenter::OnPredict()
{
    if(!m_controller.IsValidCompanyName(mp_ui->editCompanyName->text()))
    {
        QMessageBox::critical(this, "Error", "You must set correct company name!");
        return;
    }

    //ui->editPrediction->setText(QString::number(controller.Forecast(ui->spinCompanyNumber->value())));
    QVector<double> prediction_result = m_controller.Forecast(mp_ui->editCompanyName->text());

    mp_ui->tableResult->setRowCount(prediction_result.size());
    mp_ui->tableResult->setVerticalHeaderLabels(_FormSequentialDates(m_controller.GetDataModel()->GetStartDate(), m_controller.GetDataModel()->GetObservationNumber()));

    for(int i = 0; i<prediction_result.size(); ++i)
        mp_ui->tableResult->setItem(i, 0, new QTableWidgetItem(QString::number(prediction_result[i])));
}

void Presenter::OnCellClicked(int , int j)
{
    mp_ui->editCompanyName->setText(mp_ui->tableData->horizontalHeaderItem(j)->text());
}
