#ifndef FORECASTMODEL_H
#define FORECASTMODEL_H

#include <QMetaType>
#include <QVector>

#include "matrix.h"

class ForecastModel
{

public:
    ForecastModel();
    ForecastModel(const QVector<int>& i_a);

    double Evaluate(const QVector<double> i_a);
    void SetUp(const Matrix::TVariable& y,const Matrix& X);
    double Quality() const;

    void SetParams(QVector<int>& i_a);
    QVector<int> GetParams() const;

    ForecastModel operator +(ForecastModel& i_other) const;
    bool operator ==(const ForecastModel& i_other) const;

private :

    bool _DoubleVectorEqual(const QVector<double>& i_a, const QVector<double>& i_b) const;

    bool m_is_computed;
    double m_quality;
    QVector<double> m_w; // factors in regression model
    QVector<int> m_a; // variables in regression model
};

Q_DECLARE_METATYPE(ForecastModel)

#endif // FORECASTMODEL_H
