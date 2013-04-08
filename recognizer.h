// Model - mathematical model for prediction
// Steps of algorithm :
// 1.)


#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <datamodel.h>
#include <QDate>

#include "modelgenerator.h"

class Recognizer
{
public:
    Recognizer(DataModel* ip_data);
    Recognizer();

    double Forecast();


    void SetMaxPower(int i_max_power);
    void SetData(DataModel* ip_data);

    static const int NOT_VALID = -1; // should be implemented
    static bool IsValidResult(double i_price) {return i_price != NOT_VALID;}

private :
    double _EvaluateModel();
    void _CreateModel();

    bool m_is_created;

    QVector<ForecastModel> m_models;

    DataModel* mp_data;
    int m_max_power;
};

#endif // RECOGNIZER_H
