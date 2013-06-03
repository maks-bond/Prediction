#include "forecaster.h"

#include "datamodel.h"
#include "abstractgmdh.h"

#include <stdexcept>

Forecaster::Forecaster()
{
    m_ratio = 0.5;
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
    for(int i=0;i<i_matrix.GetVariablesNumber();i++){
        Matrix::TVariable cur = i_matrix.GetVariable(i);
        Matrix::TVariable cur_mod;
        for(int j=0;j<i_matrix.GetObservationNumber()*m_ratio;j++){
            cur_mod.push_back(cur[j]);
        }
    }
    return res;
}

Matrix::TVariable Forecaster::_GetTrainingDataY(const Matrix::TVariable &i_vector)
{
    Matrix::TVariable res;

    for(int i=0;i<i_vector.size()*m_ratio;i++){
        res.push_back(i_vector[i]);
    }

    return res;
}

void Forecaster::SetTrainingRatio(double i_ratio)
{
    m_ratio = i_ratio;
}
