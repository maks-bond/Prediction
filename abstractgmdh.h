#ifndef ABSTRACTGMDH_H
#define ABSTRACTGMDH_H

#include "basicmodel.h"
#include "forecastmodel.h"
#include "matrix.h"

#include <QMetaType>
#include <QVector>

class AbstractGMDH
{
public:
    AbstractGMDH();
    virtual ~AbstractGMDH(){}

    void SetData(const Matrix& i_X,const Matrix::TVariable& i_y);
    void CreateModels(int i_max_power);
    double Evaluate(const Matrix::TTimeSlice& i_time_slice);

protected:
    typedef QVector<ForecastModel> TForecastModels;

    virtual bool _CompareLevels(const TForecastModels& i_prev_models, const TForecastModels& i_cur_models) = 0;
    virtual TForecastModels _CreateBestModels(const TForecastModels& i_prev_models);
    virtual void _FilterBestModels() = 0;
    virtual double _Evaluate(const Matrix::TTimeSlice& i_time_slice) = 0;

    Matrix::TTimeSlice _GenForecastModelTimeSlice(const ForecastModel & i_model,
                                                  const Matrix::TTimeSlice& i_time_slice);

    TForecastModels m_best_models;

private:
    void _SetUpBestModels();
    Matrix _GenForecastModelData(const ForecastModel &i_model);


    Matrix m_X;
    Matrix::TVariable m_y;
    BasicModel m_basic_model;
    bool m_is_computed;
};

//Q_DECLARE_METATYPE(AbstractGMDH)

#endif // ABSTRACTGMDH_H
