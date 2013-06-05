#include "controller.h"

#include "datamodel.h"

#include "csv.h"
#include "multiseriesgmdh.h"

#include <stdexcept>

#include <QDir>
#include <QString>
#include <QVector>

namespace
{
    DataModel* _CreateDataModel(const QDir& i_dir)
    {
        DataModel* p_data_model = new DataModel();

        QVector<QString> files = CSV::Find(i_dir);

        for(int i = 0; i<files.size(); ++i)
        {
            p_data_model->AddCompanyData(CSV::Read(files[i]));
        }

        return p_data_model;
    }
}

Controller::Controller()
    : mp_data_model(0)
    , mp_gmdh(new MultiSeriesGMDH())
{
}

Controller::~Controller()
{
    delete mp_gmdh;
    delete mp_data_model;
}

void Controller::Initialize(const QDir &i_dir)
{
    delete mp_data_model;
    mp_data_model = _CreateDataModel(i_dir);
    m_forecaster.SetData(mp_data_model);
    m_forecaster.SetForecastAlgorithm(mp_gmdh);
}

bool Controller::IsInitialized() const
{
    return mp_data_model;
}

const DataModel *Controller::GetDataModel() const
{
    return mp_data_model;
}

bool Controller::IsValidCompanyName(const QString &i_comp_name)
{
    return mp_data_model->IsValidCompanyName(i_comp_name);
}

double Controller::GetTrainingRatio() const
{
    return m_forecaster.GetTrainingRatio();
}

void Controller::SetTrainingRatio(double i_ratio)
{
    m_forecaster.SetTrainingRatio(i_ratio);
}

void Controller::SetTimeStep(int i_time_step)
{
    m_forecaster.SetTimeStep(i_time_step);
}

QString Controller::GetPredictedCompanyName() const
{
    return m_predicted_company_name;
}

Matrix::TVariable Controller::GetPrediction() const
{
    return m_prediction;
}

void Controller::Forecast(const QString& i_company_name)
{
    if(mp_data_model->IsValidCompanyName(i_company_name) == false)
        throw std::logic_error("Bad index");

    m_prediction.clear();
    QDate cur_date = mp_data_model->GetStartDate();

    for(int i=0;i<mp_data_model->GetObservationNumber();i++){
        double cur_res = m_forecaster.Forecast(i_company_name,cur_date);
        m_prediction.push_back(cur_res);
        cur_date = cur_date.addDays(1);
    }

    m_predicted_company_name = i_company_name;
}

