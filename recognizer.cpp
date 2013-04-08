#include "recognizer.h"


Recognizer::Recognizer(DataModel* ip_data)
    : m_is_created(false), m_max_power(1)
{
    if(ip_data->IsValid()) mp_data = ip_data;
    else mp_data = NULL;
}

Recognizer::Recognizer()
    : m_is_created(false), m_max_power(1)
{

}

double Recognizer::Forecast()
{
    if(!mp_data->IsValid()) return NOT_VALID;
    if(!m_is_created) _CreateModel();
    return _EvaluateModel();
}

void Recognizer::SetMaxPower(int max_power)
{
    if(max_power <= 0 || max_power == m_max_power) return;
    m_max_power = max_power;
    m_is_created = false;
}

void Recognizer::SetData(DataModel* data)
{
    if(data->IsValid()){
        mp_data = data;
        m_is_created = false;
    }
}

void Recognizer::_CreateModel()
{
    BasicModel basic_model = ModelGenerator::GenerateBasicModel(mp_data->GetCompanyNumber(),m_max_power);
    QVector<ForecastModel> prev_level_models;
    QVector<ForecastModel> cur_level_models = ModelGenerator::GenerateForecastModels(basic_model);
    /*
    while(CompareLevels(prev_level_models, cur_level_models))
    {
        prev_level_models = cur_level_models;
        cur_level_models = CreateCandidateModels(cur_level_models);
        ComputeCandidateModels(cur_level_models);
        //EvaluateCandidateModels(cur_level_models);
        FilterCandidateModels(cur_level_models);
    }
    */
}

/*
QVector<ForecastModel> Recognizer::CreateCandidateModels(QVector<ForecastModel>& i_models){
    QVector<ForecastModel> res;
    for(int i=0;i<i_models.size();i++){
        for(int j=i+1;j<i_models.size();j++){
            ForecastModel cur_model = i_models[i] + i_models[j];
            res.append(cur_model);
        }
    }
    return res;
}
*/

double Recognizer::_EvaluateModel()
{
    return NOT_VALID;
}
