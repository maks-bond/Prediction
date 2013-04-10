#include "datamodel.h"
#include "datacompany.h"

#include <stdexcept>

DataModel::DataModel()
{
}

void DataModel::SetStartDate(const QDate i_date)
{
    m_start_date = i_date;
}

void DataModel::AddCompany(const DataCompany &i_data_company)
{
    if(i_data_company.GetStartDate() != m_start_date)
        throw std::logic_error("Bad date!");

    m_data.PushVariable(i_data_company.GetPrices());
    m_companies_names.push_back(i_data_company.GetCompanyName());
}

const Matrix &DataModel::GetRawData() const
{
    return m_data;
}

bool DataModel::IsValid() const
{
    return m_start_date.isValid() && !m_data.IsEmpty() && !m_companies_names.empty();
}
