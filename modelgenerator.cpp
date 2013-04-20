#include "modelgenerator.h"

#include "mathutils.h"

namespace
{
    QVector<int> MakeVectorOfNumbers(int i_n)
    {
        QVector<int> res;

        for(int i = 0; i<i_n; ++i)
            res.push_back(i);

        return res;
    }
}

ModelGenerator::ModelGenerator()
{
}


BasicModel ModelGenerator::GenerateBasicModel(int i_number_of_companies, int i_max_generation_length)
{
    BasicModel model;
    QVector<int> elements = MakeVectorOfNumbers(i_number_of_companies);

    for(int i = 1; i<=i_max_generation_length; ++i)
    {
        QVector<int> combinations = MathUtils::GenerateCombinationsOfOneBits(i, i_number_of_companies);

        for(int j = 0; j<combinations.size(); ++j)
            model.push_back(MathUtils::ApplyMaskForElements(elements, combinations[j]));
    }

    return model;
}

QVector<ForecastModel> ModelGenerator::GenerateForecastModels(const BasicModel &i_basic_model)
{
    return QVector<ForecastModel>();
}
