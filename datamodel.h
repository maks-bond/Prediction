#ifndef MODELFORECASTING_H
#define MODELFORECASTING_H

#include <QVector>

class DataCompany;

typedef QVector<DataCompany*> TCompanies;

class DataModel
{
public:
    DataModel();
    ~DataModel();

    void AddCompany(DataCompany* ip_model_company);
    TCompanies GetCompaniesData() const;
    bool IsValid() const;

private:
    TCompanies m_model;
};

#endif // MODELFORECASTING_H
