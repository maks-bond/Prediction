#include "datamodel.h"
#include "datacompany.h"

#include <stdexcept>

DataModel::DataModel()
{
}

/*void DataModel::SetStartDate(const QDate i_date)
{
    m_start_date = i_date;
}*/

const QDate& DataModel::GetStartDate() const
{
    return m_start_date;
}

void DataModel::AddCompanyData(const DataCompany &i_data_company)
{
    if(m_data.IsEmpty())
        m_start_date = i_data_company.GetStartDate();

    if(i_data_company.GetStartDate() != m_start_date)
        throw std::logic_error("Bad date!");

    m_data.PushVariable(i_data_company.GetPrices());
    m_companies_names.push_back(i_data_company.GetCompanyName());
}

const QString &DataModel::GetCompanyName(int i_index) const
{
    if(i_index < 0 || i_index >= m_companies_names.size())
        throw std::logic_error("Bad index");

    return m_companies_names[i_index];
}

int DataModel::GetCompaniesNumber() const
{
    return m_companies_names.size();
}

int DataModel::GetObservationNumber() const
{
    return m_data.GetObservationNumber();
}

const Matrix::TVariable& DataModel::GetVariable(const QString &i_comp_name) const
{
    int ind = m_companies_names.indexOf(i_comp_name);
    if(ind == -1) throw std::logic_error("can't find company in DataModel");
    return m_data.GetVariable(ind);
}

Matrix DataModel::GetRawDataExcept(const QString &i_comp_name) const
{
    int ind = m_companies_names.indexOf(i_comp_name);

    if(ind == -1) throw std::logic_error("can't find company in DataModel");

    Matrix res(m_data);
    res.RemoveVariable(ind);

    return res;
}

double DataModel::GetObservation(const QDate &i_date, const QString &i_comp_name)
{
    int ind = m_companies_names.indexOf(i_comp_name);
    if(ind == -1) throw std::logic_error("can't find company in DataModel");

    return m_data.GetObservation(ind,m_start_date.daysTo(i_date));
}

Matrix::TTimeSlice DataModel::GetTimeSliceExcept(const QDate &i_date, const QString &i_comp_name) const
{
    if(i_date < m_start_date || i_date >= m_start_date.addDays(m_data.GetObservationNumber()))
        throw std::logic_error("Date is wrong");

    int ind = m_companies_names.indexOf(i_comp_name);
    if(ind == -1) throw std::logic_error("can't find company in DataModel");

    Matrix::TFilter filter;
    filter.insert(ind);

    return m_data.GetTimeSlice(m_start_date.daysTo(i_date),filter);
}

const Matrix &DataModel::GetRawData() const
{
    return m_data;
}

bool DataModel::IsValid() const
{
    return m_start_date.isValid() && !m_data.IsEmpty() && !m_companies_names.empty();
}

bool DataModel::IsValidCompanyName(const QString &i_comp_name)
{
    return m_companies_names.indexOf(i_comp_name) != -1;
}
