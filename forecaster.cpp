#include "forecaster.h"

#include "datamodel.h"
#include "abstractgmdh.h"

#include <stdexcept>

Forecaster::Forecaster()
{
}

double Forecaster::Forecast()
{
    if(!mp_data || !mp_data->IsValid() || !mp_gmdh_algo)
        throw std::logic_error("Data Model is not valid");

    // create gmdh models
    mp_gmdh_algo->SetData(mp_data->GetRawData());
    //Someone must set up here the max power coef!!!
    mp_gmdh_algo->CreateModels(2);
    return mp_gmdh_algo->Evaluate(mp_data->GetRawData());
}

void Forecaster::SetData(const DataModel* data)
{
    if(data->IsValid()) mp_data = data;
}

void Forecaster::SetForecastAlgorithm(AbstractGMDH *i_gmdh_algo)
{
    mp_gmdh_algo = i_gmdh_algo;
}


