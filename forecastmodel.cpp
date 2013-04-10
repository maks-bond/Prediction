#include "forecastmodel.h"

ForecastModel::ForecastModel()
    : m_is_comptuted(false), m_quality(-1)
{

}

ForecastModel::ForecastModel(QVector<int> &i_a)
    : m_is_comptuted(false), m_a(i_a), m_quality(-1)
{

}

double ForecastModel::Evaluate(const QVector<double> i_a)
{
    if(!m_is_comptuted) _Compute();
    double res = 0;

    for(int j=0;j<i_a.size();j++) res+= i_a[j]*m_w[j];

    return res;
}


void ForecastModel::_Compute()
{
    if(m_is_comptuted) return;

    //implement

    m_is_comptuted = true;
}


double ForecastModel::Quality()
{
    if(m_quality != -1) return m_quality;
    if(!m_is_comptuted) _Compute();

    m_quality = 0;
    // implement

    return m_quality;
}

void ForecastModel::SetParams(QVector<int>& i_a)
{
    if(m_a == i_a) return;
    m_a = i_a;
    m_is_comptuted = false;
}

ForecastModel ForecastModel::operator +(const ForecastModel &i_other) const
{
    return ForecastModel();
}
