#include "datacompany.h"

DataCompany::DataCompany()
{
    m_period_start = QDate::currentDate();
}

DataCompany::~DataCompany()
{
}

void DataCompany::AddSeqPrice(double i_price)
{
    m_model.append(i_price);
}

void DataCompany::SetCompanyName(const QString &i_company_name)
{
    m_company_name = i_company_name;
}

void DataCompany::SetStartPeriod(const QDate &i_period_start)
{
    m_period_start = i_period_start;
}

QString DataCompany::GetCompanyName() const
{
    return m_company_name;
}

TPrices DataCompany::GetPrices() const
{
    return m_model;
}

QDate DataCompany::GetStartPeriod() const
{
    return m_period_start;
}
