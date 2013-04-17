#ifndef FORECASTMODEL_H
#define FORECASTMODEL_H

#include <QVector>

#include "matrix.h"

class ForecastModel
{

public:
    ForecastModel();
    ForecastModel(QVector<int>& i_a);

    double Evaluate(const QVector<double> i_a);
    void SetUp(const Matrix::TVariable& y,const Matrix& X);
    double Quality();

    void SetParams(QVector<int>& i_a);
    QVector<int> GetParams();

    ForecastModel operator +(ForecastModel& i_other) const;

private :
    bool m_is_computed;
    double m_quality;
    QVector<double> m_w; // factors in regression model
    QVector<int> m_a; // variables in regression model

};

#endif // FORECASTMODEL_H
