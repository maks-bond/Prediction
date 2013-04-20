#ifndef MULTISERIESGMDH_H
#define MULTISERIESGMDH_H

#include "abstractgmdh.h"

class MultiSeriesGMDH : public AbstractGMDH
{
public:
    MultiSeriesGMDH();

private:
    virtual bool _CompareLevels(const TForecastModels& i_prev_models, const TForecastModels& i_cur_models);
    virtual void _FilterBestModels();
    virtual void _Evaluate(const Matrix::TTimeSlice& i_time_slice);
};

#endif // MULTISERIESGMDH_H
