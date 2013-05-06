#ifndef MULTISERIESGMDHTEST_H
#define MULTISERIESGMDHTEST_H

#include <QObject>

class MultiSeriesGMDHTest : public QObject
{
    Q_OBJECT
public:
    MultiSeriesGMDHTest(QObject *parent = 0);

private slots :
    void EvaluateTest();
    void EvaluateTest_data();

    void GenForecastModelData();
    void GenForecastModelData_data();

};

#endif // MULTISERIESGMDHTEST_H
