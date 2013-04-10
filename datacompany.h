#ifndef MODELCOMPANY_H
#define MODELCOMPANY_H

#include "mathstructures.h"

#include <QDate>

class DataCompany
{
public:
    DataCompany();

    void PushPrice(double i_price);

    void SetCompanyName(const QString& i_company_name);
    void SetStartDate(const QDate& i_period_start);
    QString GetCompanyName() const;
    QDate GetStartDate() const;
    Matrix::TVariable GetPrices() const;

private:
    QDate m_start_date;
    QString m_company_name;
    Matrix::TVariable m_prices;
};

#endif // MODELCOMPANY_H
