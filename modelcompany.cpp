#include "modelcompany.h"
#include "modelItem.h"

ModelCompany::ModelCompany(QObject *parent)
    : QObject(parent)
{
}

ModelCompany::~ModelCompany()
{
    for(int i = 0; i<m_model.size(); ++i)
    {
        delete m_model[i];
        delete m_object_model[i];
    }
}

void ModelCompany::AddItem(ModelItem* i_model_item)
{
    m_model.append(i_model_item);
    m_object_model.append(i_model_item);
}

void ModelCompany::SetCompanyName(const QString &i_company_name)
{
    m_company_name = i_company_name;
}

QList<ModelItem*> ModelCompany::GetListOfItems() const
{
    return m_model;
}

QList<QObject*> ModelCompany::GetListOfObjectItems() const
{
    return m_object_model;
}
