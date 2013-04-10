// Model - mathematical model for prediction
// Steps of algorithm :
// 1.)


#ifndef RECOGNIZER_H
#define RECOGNIZER_H

class DataModel;
class AbstractGMDH;

class Forecaster
{
public:
    Forecaster();

    double Forecast();

    void SetData(const DataModel* ip_data);
    void SetForecastAlgorithm(AbstractGMDH* i_gmdh_algo);

private :
    static int const mg_max_power = 2;
    AbstractGMDH* mp_gmdh_algo;
    const DataModel* mp_data;
};

#endif // RECOGNIZER_H
