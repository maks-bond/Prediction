#include "forecaster.h"

#include "datamodel.h"
#include "abstractgmdh.h"

#include <stdexcept>

Forecaster::Forecaster()
{
    m_ratio = 0.5;
    m_time_step = 0;
}

double Forecaster::Forecast(const QString& i_comp_name, const QDate& i_date)
{
    if(!mp_data || !mp_data->IsValid() || !mp_gmdh_algo)
        throw std::logic_error("Data Model is not valid");

    // create gmdh models
    Matrix raw_data_x = mp_data->GetRawDataExcept(i_comp_name);
    Matrix::TVariable raw_data_y = mp_data->GetVariable(i_comp_name);
    mp_gmdh_algo->SetData(_GetTrainingDataX(raw_data_x),_GetTrainingDataY(raw_data_y));
    //Someone must set up here the max power coef!!!
    mp_gmdh_algo->CreateModels(2);
    return mp_gmdh_algo->Evaluate(mp_data->GetTimeSliceExcept(i_date, i_comp_name));
}

void Forecaster::SetData(const DataModel* data)
{
    if(data->IsValid()) mp_data = data;
}

void Forecaster::SetForecastAlgorithm(AbstractGMDH *ip_gmdh_algo)
{
    mp_gmdh_algo = ip_gmdh_algo;
}

Matrix Forecaster::_GetTrainingDataX(const Matrix &i_matrix)
{
    Matrix res;

    for(int i=0;i<i_matrix.GetVariablesNumber();i++)
    {
        Matrix::TVariable cur = i_matrix.GetVariable(i);
        res.PushVariable(cur.mid(0, i_matrix.GetObservationNumber()*m_ratio - mg_time_diff));
    }

    return res;
}

Matrix::TVariable Forecaster::_GetTrainingDataY(const Matrix::TVariable &i_vector)
{
    return i_vector.mid(mg_time_diff, i_vector.size()*m_ratio);
}

void Forecaster::SetTrainingRatio(double i_ratio)
{
    m_ratio = i_ratio;
}

void Forecaster::SetTimeStep(int i_time_step)
{
    m_time_step = i_time_step;
}
