#include "modelgenerator.h"

ModelGenerator::ModelGenerator()
{
}


BasicModel ModelGenerator::GenerateBasicModel(int i_number_of_companies, int i_max_generation_length)
{
    return BasicModel();
}

QVector<ForecastModel> ModelGenerator::GenerateForecastModels(const BasicModel &i_basic_model)
{
    return QVector<ForecastModel>();
}
