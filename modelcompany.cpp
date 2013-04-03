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

    QDate cur_date = QDate::fromString(i_model_item->date(),"yyyy-M-d");

    if(cur_date.isValid()){
        m_model.append(i_model_item);
        m_object_model.append(i_model_item);

        if(!m_period_start.isValid() || cur_date < m_period_start)
            m_period_start = cur_date;

        if(!m_period_end.isValid() || cur_date > m_period_end)
            m_period_end = cur_date;
    }
}

void ModelCompany::SetCompanyName(const QString &i_company_name)
{
    m_company_name = i_company_name;
}

QString ModelCompany::GetCompanyName() const
{
    if(m_company_name.isEmpty())
        return m_company_name;
    else
        return NULL;
}

QList<ModelItem*> ModelCompany::GetListOfItems() const
{
    return m_model;
}

QList<QObject*> ModelCompany::GetListOfObjectItems() const
{
    return m_object_model;
}

QDate ModelCompany::getStartPeriod() const
{
    return m_period_start;
}

QDate ModelCompany::getEndPeriod() const
{
    return m_period_end;
}
