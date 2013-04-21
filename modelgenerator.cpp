#include "modelgenerator.h"

namespace
{
    QVector<int> MakeVectorOfNumbers(int i_n)
    {
        QVector<int> res;

        for(int i = 0; i<i_n; ++i)
            res.push_back(i);

        return res;
    }

    const int g_number_of_begin_forecast_model_variables = 2;
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
        QVector<int> combinations = ModelGenerator::GenerateCombinationsOfOneBits(i, i_number_of_companies);

        for(int j = 0; j<combinations.size(); ++j)
            model.push_back(ModelGenerator::ApplyMaskForElements(elements, combinations[j]));
    }

    return model;
}

QVector<ForecastModel> ModelGenerator::GenerateForecastModels(const BasicModel &i_basic_model)
{
    QVector<ForecastModel> result;

    QVector<int> combinations = ModelGenerator::GenerateCombinationsOfOneBits(g_number_of_begin_forecast_model_variables
                                                                         , i_basic_model.size());

    for(int j = 0; j<combinations.size(); ++j)
        result.push_back(ForecastModel(ModelGenerator::GetOneBitsIndexes(combinations[j])));

    return result;
}

int ModelGenerator::Snoob(int i_x)
{
    unsigned u_x = static_cast<unsigned>(i_x);
    unsigned rightOne;
    unsigned nextHigherOneBit;
    unsigned rightOnesPattern;

    unsigned next = 0;

    if(u_x)
    {

    // right most set bit
    rightOne = u_x & -(signed)u_x;

    // reset the pattern and set next higher bit
    // left part of x will be here
    nextHigherOneBit = u_x + rightOne;

    // nextHigherOneBit is now part [D] of the above explanation.

    // isolate the pattern
    rightOnesPattern = u_x ^ nextHigherOneBit;

    // right adjust pattern
    rightOnesPattern = (rightOnesPattern)/rightOne;

    // correction factor
    rightOnesPattern >>= 2;

    // rightOnesPattern is now part [A] of the above explanation.

    // integrate new pattern (Add [D] and [A])
    next = nextHigherOneBit | rightOnesPattern;
    }

    return next;
}

int ModelGenerator::GenerateMinimumNumberOfBits(int i_bits)
{
    if(i_bits<=0)
        throw std::logic_error("Bad number of bits");

    return (1<<i_bits)-1;
}

int ModelGenerator::GenerateMaximumNumberOfBits(int i_bits, int i_max_bit)
{
    if(i_bits > i_max_bit || i_bits <= 0)
        throw std::logic_error("Bad number of bits");

    return GenerateMinimumNumberOfBits(i_bits)<<(i_max_bit - i_bits);
}

QVector<int> ModelGenerator::GenerateCombinationsOfOneBits(int i_bits, int i_max_bits)
{
    QVector<int> result;

    int cur = GenerateMinimumNumberOfBits(i_bits);

    while(cur<=GenerateMaximumNumberOfBits(i_bits, i_max_bits))
    {
        result.push_back(cur);
        cur = Snoob(cur);
    }

    return result;
}

QVector<int> ModelGenerator::GetOneBitsIndexes(int i_n)
{
    QVector<int> result;
    int cur_ind = 0;

    while(i_n)
    {
        if(i_n&1)
            result.push_back(cur_ind);

        cur_ind++;
        i_n>>=1;
    }

    return result;
}
