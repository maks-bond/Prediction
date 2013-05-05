#ifndef FORECASTMODELTEST_H
#define FORECASTMODELTEST_H

#include <QObject>

class forecastmodeltest : public QObject
{
    Q_OBJECT
public:
    explicit forecastmodeltest(QObject *parent = 0);
    
private slots:
    void SetUpTest();
    void SetUpTest_data();
};

#endif // FORECASTMODELTEST_H
