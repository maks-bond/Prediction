#include "abstractgmdh.h"

#include "modelgenerator.h"

#include <stdexcept>

AbstractGMDH::AbstractGMDH()
    : m_is_computed(false)
{
}

void AbstractGMDH::SetData(const Matrix &i_data)
{
    m_data = i_data;
}

void AbstractGMDH::CreateModels(int i_max_power)
{
    if(m_data.IsEmpty())
        throw std::logic_error("You must set up data!");

    BasicModel basic_model = ModelGenerator::GenerateBasicModel(m_data.GetVariablesNumber()
                                                                , i_max_power);
    TForecastModels prev_level_models;
    m_best_models = ModelGenerator::GenerateForecastModels(basic_model);
    while(_CompareLevels(prev_level_models, m_best_models))
    {
        prev_level_models = m_best_models;
        m_best_models = _CreateBestModels(m_best_models);
        //Least squares is here
        _SetUpBestModels();
        _FilterBestModels();
    }

    m_is_computed = true;
}

double AbstractGMDH::Evaluate(const Matrix& i_evaluation_data)
{
    if(!m_is_computed)
        throw std::logic_error("Models must be computed!");

    //Here we must store the matrix by reference!!!
    _Evaluate(i_evaluation_data);
    return 0;
}

AbstractGMDH::TForecastModels AbstractGMDH::_CreateBestModels(const AbstractGMDH::TForecastModels &i_prev_models)
{
    TForecastModels res;
    for(int i=0;i<i_prev_models.size();i++){
        for(int j=i+1;j<i_prev_models.size();j++){
            ForecastModel cur_model = i_prev_models[i] + i_prev_models[j];
            res.append(cur_model);
        }
    }
    return res;
}


void AbstractGMDH::_SetUpBestModels()
{
}
