#ifndef MULTISERIESGMDH_H
#define MULTISERIESGMDH_H

#include "abstractgmdh.h"

#include <QMetaType>

class MultiSeriesGMDH : public AbstractGMDH
{
public:
    MultiSeriesGMDH();

protected:
    virtual bool _CompareLevels(const TForecastModels& i_prev_models, const TForecastModels& i_cur_models);
    virtual void _FilterBestModels();
    virtual double _Evaluate(const Matrix::TTimeSlice& i_time_slice);
};

Q_DECLARE_METATYPE(MultiSeriesGMDH)

#endif // MULTISERIESGMDH_H
