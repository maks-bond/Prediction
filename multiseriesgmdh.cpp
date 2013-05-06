#include "multiseriesgmdh.h"

MultiSeriesGMDH::MultiSeriesGMDH()
{
}

bool MultiSeriesGMDH::_CompareLevels(const AbstractGMDH::TForecastModels &i_prev_models, const AbstractGMDH::TForecastModels &i_cur_models)
{
    return i_prev_models[0].Quality() > i_cur_models[0].Quality();
}

void MultiSeriesGMDH::_FilterBestModels()
{
    int min_index = 0;
    double min_error = m_best_models[0].Quality();
    for(int i=1;i<m_best_models.size();i++){
        if(m_best_models[i].Quality() < min_error){
            min_error = m_best_models[i].Quality();
            min_index = i;
        }
    }
    ForecastModel best = m_best_models[min_index];
    m_best_models.clear();
    m_best_models.push_back(best);
}

double MultiSeriesGMDH::_Evaluate(const Matrix::TTimeSlice &i_time_slice)
{
    double res = 0;
    int n = m_best_models.size();

    for(int i=0;i<n;i++){
        res += m_best_models[i].Evaluate(i_time_slice);
    }

    return res/n;
}
