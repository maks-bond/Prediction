#ifndef MODELFORECASTING_H
#define MODELFORECASTING_H

#include "datacompany.h"
#include "matrix.h"

#include <QDate>
#include <QMetaType>
#include <QVector>


typedef QVector<QString> TCompaniesNames;

class DataModel
{
public:
    DataModel();

    //void SetStartDate(const QDate i_date);
    const QDate& GetStartDate() const;
    void AddCompanyData(const DataCompany& i_data_company);
    const Matrix::TVariable& GetVariable(const QString& i_comp_name) const;
    Matrix GetRawDataExcept(const QString& i_comp_name) const;
    Matrix::TTimeSlice GetTimeSliceExcept(const QDate& i_date, const QString& i_comp_name) const;
    const Matrix& GetRawData() const;
    bool IsValid() const;

private:
    //TCompanies m_model;
    TCompaniesNames m_companies_names;
    QDate m_start_date;
    Matrix m_data;
};

Q_DECLARE_METATYPE(DataModel)

#endif // MODELFORECASTING_H
