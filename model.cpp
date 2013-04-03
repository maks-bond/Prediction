#include "model.h"

#include "modelcompany.h"

Model::Model(QObject *parent) :
    QObject(parent)
{
}

Model::~Model()
{
    for(int i = 0; i<m_model.size(); ++i)
    {
        delete m_model[i];
    }
}

void Model::AddCompany(ModelCompany* i_model_company)
{
    m_model.append(i_model_company);
    m_names.append(i_model_company->GetCompanyName());
}

QVector<ModelCompany*> Model::GetListOfCompanies() const
{
    return m_model;
}

QVector<QString> Model::GetCompanyNames() const
{
    return m_names;
}

bool Model::HasCompanies() const
{
    return !m_model.empty();
}
