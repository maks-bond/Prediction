#include "forecaster.h"

#include "datamodel.h"
#include "abstractgmdh.h"

#include <stdexcept>

Forecaster::Forecaster()
{
}

double Forecaster::Forecast(const QString& i_comp_name, const QDate& i_date)
{
    if(!mp_data || !mp_data->IsValid() || !mp_gmdh_algo)
        throw std::logic_error("Data Model is not valid");

    // create gmdh models
    mp_gmdh_algo->SetData(mp_data->GetRawDataExcept(i_comp_name),mp_data->GetVariable(i_comp_name));
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


