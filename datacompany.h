#ifndef MODELCOMPANY_H
#define MODELCOMPANY_H

#include <QVector>
#include <QDate>

typedef QVector<double> TPrices;

class DataCompany
{
public:
    DataCompany();
    ~DataCompany();

    // add sequential price to data table
    void AddSeqPrice(double i_price);

    void SetCompanyName(const QString& i_company_name);
    void SetStartPeriod(const QDate& i_period_start);
    QString GetCompanyName() const;
    QDate GetStartPeriod() const;
    TPrices GetPrices() const;

private:
    QDate m_period_start;
    QString m_company_name;
    TPrices m_model;
};

#endif // MODELCOMPANY_H
