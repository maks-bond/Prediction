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

    BasicModel m_basic_model = ModelGenerator::GenerateBasicModel(m_X.GetVariablesNumber()
                                                                , i_max_power);
    TForecastModels prev_level_models;
    m_best_models = ModelGenerator::GenerateForecastModels(m_basic_model);
    //Filter can be here
    _SetUpBestModels();

    do
    {
        prev_level_models = m_best_models;
        m_best_models = _CreateBestModels(m_best_models);
        //Least squares is here
        _SetUpBestModels();
        _FilterBestModels();
    } while(_CompareLevels(prev_level_models, m_best_models));

    m_best_models = prev_level_models;
    m_is_computed = true;
}

double AbstractGMDH::Evaluate(const Matrix::TTimeSlice &i_time_slice)
{
    if(!m_is_computed)
        throw std::logic_error("Models must be computed!");

    //Here we must store the matrix by reference!!!
    return _Evaluate(i_time_slice);
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
        cur_model.SetUp(m_y,_GenForecastModelData(cur_model));//m_X.Filter(cur_model.GetParams()));
    }
}

Matrix AbstractGMDH::_GenForecastModelData(const ForecastModel &i_model)
{
    QVector<int> a = i_model.GetParams();
    Matrix res;
    for(int i = 0; i < a.size(); i++){
        Component c = m_basic_model[a[i]];
        if(c.size()==1){
            res.PushVariable(m_X.GetVariable(c[0]));
        }
        else{
            Matrix::TVariable com_var = m_X.GetVariable(c[0]), cur_var;
            for(int j=1;j<c.size();j++){
                cur_var = m_X.GetVariable(c[j]);
                for(int k=0;k<cur_var.size();k++){
                    com_var[k] *= cur_var[k];
                }
            }
            res.PushVariable(com_var);
        }
    }

    return res;
}
