#include "datacompany.h"

#include <stdexcept>

DataCompany::DataCompany()
{
}

void DataCompany::PushPrice(double i_price)
{
    m_prices.push_back(i_price);
}

void DataCompany::SetCompanyName(const QString &i_company_name)
{
    m_company_name = i_company_name;
}

void DataCompany::SetStartDate(const QDate &i_start_date)
{
    m_start_date = i_start_date;
}

QString DataCompany::GetCompanyName() const
{
    if(m_company_name.isEmpty())
        throw std::logic_error("Company name is not valid!");

    return m_company_name;
}


QDate DataCompany::GetStartDate() const
{
    if(m_start_date.isNull())
        throw std::logic_error("Start date is not valid!");

    return m_start_date;
}

Matrix::TVariable DataCompany::GetPrices() const
{
    if(m_prices.empty())
        throw std::logic_error("Prices is not valid!");

    return m_prices;
}
