#include "datamodel.h"
#include "datacompany.h"

DataModel::DataModel()
{
}

DataModel::~DataModel()
{
    for(int i = 0; i<m_model.size(); ++i)
    {
        delete m_model[i];
    }
}

void DataModel::AddCompany(DataCompany* ip_model_company)
{
    m_model.append(ip_model_company);
}

TCompanies DataModel::GetCompaniesData() const
{
    return m_model;
}

int DataModel::GetCompanyNumber() const
{
    return m_model.size();
}

bool DataModel::IsValid() const
{
    return !m_model.empty();
}
