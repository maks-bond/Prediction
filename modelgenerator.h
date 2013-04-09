#ifndef MODELGENERATOR_H
#define MODELGENERATOR_H

#include <basicmodel.h>
#include <forecastmodel.h>

class ModelGenerator
{
public:
    static BasicModel GenerateBasicModel(int i_number_of_companies, int i_max_generation_length);
    static QVector<ForecastModel> GenerateForecastModels(const BasicModel& i_basic_model);

private:
    ModelGenerator();    
};

#endif // MODELGENERATOR_H
