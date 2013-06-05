#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "forecaster.h"
#include "matrix.h"

#include <QVector>

class QDir;
class QString;
class DataModel;
class AbstractGMDH;

class Controller
{
public:
    Controller();
    ~Controller();

    void Initialize(const QDir& i_dir);
    bool IsInitialized() const;

    const DataModel* GetDataModel() const;
    bool IsValidCompanyName(const QString& i_comp_name);

    void SetTrainingRatio(double i_ratio);
    void SetTimeStep(int i_time_step);

    QString GetPredictedCompanyName() const;
    Matrix::TVariable GetPrediction() const;

    void Forecast(const QString& i_company_name);

private:
    DataModel* mp_data_model;
    AbstractGMDH* mp_gmdh;
    Forecaster m_forecaster;

    QString m_predicted_company_name;
    Matrix::TVariable m_prediction;
};

#endif // CONTROLLER_H
