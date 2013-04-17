#include "abstractgmdh.h"
#include "modelgenerator.h"

#include <stdexcept>

AbstractGMDH::AbstractGMDH()
    : m_is_computed(false)
{
}

void AbstractGMDH::SetData(const Matrix &i_X, const Matrix::TVariable &i_y)
{
    m_y = i_y;
    m_X = i_X;
}

void AbstractGMDH::CreateModels(int i_max_power)
{
    if(m_X.IsEmpty())
        throw std::logic_error("You must set up data!");

    BasicModel basic_model = ModelGenerator::GenerateBasicModel(m_X.GetVariablesNumber()
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

double AbstractGMDH::Evaluate(const Matrix::TTimeSlice &i_time_slice)
{
    if(!m_is_computed)
        throw std::logic_error("Models must be computed!");

    //Here we must store the matrix by reference!!!
    _Evaluate(i_time_slice);
    return 0;
}

AbstractGMDH::TForecastModels AbstractGMDH::_CreateBestModels(const AbstractGMDH::TForecastModels &i_prev_models)
{
    TForecastModels res;
    for(int i=0;i<i_prev_models.size();i++){
        for(int j=i+1;j<i_prev_models.size();j++){
            ForecastModel m1 = i_prev_models[i], m2 = i_prev_models[j] ;
            res.append(m1+m2);
        }
    }
    return res;
}


void AbstractGMDH::_SetUpBestModels()
{
    for(int i=0;i<m_best_models.size();i++){
        ForecastModel cur_model = m_best_models[i];
        cur_model.SetUp(m_y,m_X.Filter(cur_model.GetParams()));
    }
}
