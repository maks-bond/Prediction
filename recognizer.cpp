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
    /*
    CreateBasicModel();
    while(CompareLevels()){
        for(int i=0; i< current_models.size();i++){
            candidate_models = CreateCandidateModels(current_models[i]);
            SetUpCandidateModels(candidate_models);
            FilterCandidateModels(candidate_models);
            EvaluateCandidateModels(candidate_models);
        }
    }
    */
}

/*
Model Recognizer::CreateCandidateModels(Model& model){
    Model res;
    for(int i=0;i<model.size();i++){
        for(int j=i+1;j<model.size();j++){
            Model cur_model = model[i] + model[j];
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
