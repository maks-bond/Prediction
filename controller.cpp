#include "controller.h"

#include "datamodel.h"
#include "forecaster.h"
#include "csv.h"
#include "multiseriesgmdh.h"

#include <stdexcept>

#include <QDir>

namespace
{
    DataModel* _CreateDataModel(const QDir& i_dir)
    {
        DataModel* p_data_model = new DataModel();

        QVector<QString> files = CSV::Find(i_dir);

        for(int i = 0; i<files.size(); ++i)
        {
            p_data_model->AddCompanyData(CSV::Read(files[i]));
        }

        return p_data_model;
    }
}

Controller::Controller()
    : mp_data_model(nullptr)
    , mp_gmdh(new MultiSeriesGMDH())
{
}

Controller::~Controller()
{
    delete mp_gmdh;
    delete mp_data_model;
}

void Controller::Initialize(const QDir &i_dir)
{
    delete mp_data_model;
    mp_data_model = _CreateDataModel(i_dir);
}

bool Controller::IsInitialized() const
{
    return mp_data_model;
}

const DataModel *Controller::GetDataModel() const
{
    return mp_data_model;
}

double Controller::Forecast(int i_company_index)
{
    if(i_company_index < 0 || i_company_index >= mp_data_model->GetCompaniesNumber())
        throw std::logic_error("Bad index");

    Forecaster forecaster;
    forecaster.SetData(mp_data_model);
    forecaster.SetForecastAlgorithm(mp_gmdh);
    return forecaster.Forecast(mp_data_model->GetCompanyName(i_company_index));
}

