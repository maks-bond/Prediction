#ifndef MODELFORECASTING_H
#define MODELFORECASTING_H

#include "datacompany.h"
#include "mathstructures.h"

#include <QDate>
#include <QVector>


typedef QVector<QString> TCompaniesNames;

class DataModel
{
public:
    DataModel();

    void SetStartDate(const QDate i_date);
    void AddCompany(const DataCompany& i_data_company);
    const Matrix& GetRawData() const;
    bool IsValid() const;

private:
    //TCompanies m_model;
    TCompaniesNames m_companies_names;
    QDate m_start_date;
    Matrix m_data;
};

#endif // MODELFORECASTING_H
