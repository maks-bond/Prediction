#include "presenter.h"
#include "ui_presenter.h"

#include "datamodel.h"
#include "export.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QSplitter>
#include <QHeaderView>

#include <cmath>

namespace
{
    QStringList _FormSequentialDates(const QDate& i_start_date, int i_date_count)
    {
        QStringList res;

        for(int i = 0; i<i_date_count; ++i)
            res.push_back(i_start_date.addDays(i).toString("dd.MM.yyyy"));

        return res;
    }

    Matrix::TVariable _FormResultData(const Matrix::TVariable& i_variable, double i_training_ratio)
    {
        return i_variable.mid(i_variable.size()*i_training_ratio + 1);
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

    connect(mp_ui->tableData->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(OnSectionClicked(int)));
    connect(mp_ui->tableData->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(OnSectionClicked(int)));

    connect(mp_ui->tableData->verticalScrollBar(), SIGNAL(valueChanged(int)), mp_ui->tableResult->verticalScrollBar(), SLOT(setValue(int)));
    connect(mp_ui->tableResult->verticalScrollBar(), SIGNAL(valueChanged(int)), mp_ui->tableData->verticalScrollBar(), SLOT(setValue(int)));
    connect(mp_ui->buttonExport, SIGNAL(clicked()), this, SLOT(OnExport()));

    mp_ui->spinPercentage->setValue(50);
    mp_ui->tableResult->setColumnCount(2);
    mp_ui->tableData->verticalHeader()->setDefaultSectionSize(20);
    mp_ui->tableResult->verticalHeader()->setDefaultSectionSize(20);

    //Splitter adding
    mp_ui->layoutTables->removeWidget(mp_ui->tableData);
    mp_ui->layoutTables->removeWidget(mp_ui->tableResult);

    QSplitter* p_splitter = new QSplitter(this);
    p_splitter->addWidget(mp_ui->tableData);
    p_splitter->addWidget(mp_ui->tableResult);
    p_splitter->setStretchFactor(0, 3);
    p_splitter->setStretchFactor(1, 1);
    mp_ui->layoutTables->addWidget(p_splitter);

    QStringList right_table_labels;
    right_table_labels << "Result" << "Error";
    mp_ui->tableResult->setHorizontalHeaderLabels(right_table_labels);

}

Presenter::~Presenter()
{
    delete mp_ui;
}

void Presenter::OnExport()
{
    QDir dir = QFileDialog::getExistingDirectory(this, "Choose directory for export");

    QString company_name = m_controller.GetPredictedCompanyName();

    Matrix::TVariable true_variable = m_controller.GetDataModel()->GetVariable(company_name);
    QString true_file_name = dir.dirName() + "/" + company_name+"-True.txt";
    Export::Write(_FormResultData(true_variable, m_controller.GetTrainingRatio()), true_file_name);

    QString predicted_file_name = dir.dirName() + "/" + company_name+"-Predicted.txt";
    Export::Write(_FormResultData(m_controller.GetPrediction(), m_controller.GetTrainingRatio()), predicted_file_name);
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
    for(int i=0; i < mp_ui->tableData->columnCount();i++){
        mp_ui->tableData->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }
    mp_ui->tableResult->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    mp_ui->tableResult->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    for(int i=0; i<cols; i++){
        for(int j=0; j<rows; j++){
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(curData.GetObservation(i,j)));
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            mp_ui->tableData->setItem(j,i,item);
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

    double ratio = mp_ui->spinPercentage->value()/100.0;
    m_controller.SetTrainingRatio(ratio);
    m_controller.SetTimeStep(mp_ui->spinTimeStep->value());
    m_controller.Forecast(mp_ui->editCompanyName->text());
    QVector<double> prediction_result = m_controller.GetPrediction();

    mp_ui->tableResult->setRowCount(prediction_result.size());
    mp_ui->tableResult->setVerticalHeaderLabels(_FormSequentialDates(m_controller.GetDataModel()->GetStartDate(), m_controller.GetDataModel()->GetObservationNumber()));
    mp_ui->tableResult->setHorizontalHeaderItem(0,new QTableWidgetItem(tr("%1-Res").arg(mp_ui->editCompanyName->text())));

    QBrush gray_brush(Qt::lightGray);
    QBrush white_brush(Qt::white);

    int rows = prediction_result.size();
    int cols = mp_ui->tableData->columnCount();
    int cur_col = mp_ui->tableData->currentColumn();
    int training_count = (int)(rows*ratio) + 1;
    int test_count = rows - training_count;
    double training_error = 0;
    double test_error = 0;

    for(int i = 0; i<rows; ++i){
        double cur_comp_val = mp_ui->tableData->item(i,cur_col)->text().toDouble();
        double cur_forecast_val = prediction_result[i];
        double error = fabs(cur_forecast_val - cur_comp_val)/cur_comp_val * 100.0;
        QTableWidgetItem* cur_error_item = new QTableWidgetItem(QString::number(error));
        QTableWidgetItem* cur_item = new QTableWidgetItem(QString::number(cur_forecast_val));
        if(i < rows*ratio) {
            training_error += error;
            cur_item->setBackground(gray_brush);
            cur_error_item->setBackground(gray_brush);
        }
        else{
            test_error += error;
        }
        cur_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        cur_error_item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        mp_ui->tableResult->setItem(i, 0, cur_item);
        mp_ui->tableResult->setItem(i,1,cur_error_item);
    }

    training_error /= training_count;
    test_error /= test_count;

    mp_ui->editTestError->setText(QString::number(test_error));
    mp_ui->editTrainingError->setText(QString::number(training_error));

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            QTableWidgetItem* cur_item = mp_ui->tableData->item(i,j);
            if(i < rows*ratio) cur_item->setBackground(gray_brush);
            else cur_item->setBackground(white_brush);
        }
    }

}

void Presenter::OnCellClicked(int , int j)
{
    mp_ui->editCompanyName->setText(mp_ui->tableData->horizontalHeaderItem(j)->text());
}

void Presenter::OnSectionClicked(int i)
{
    mp_ui->editCompanyName->setText(mp_ui->tableData->horizontalHeaderItem(i)->text());
}
