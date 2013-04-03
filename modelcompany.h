#ifndef MODELCOMPANY_H
#define MODELCOMPANY_H

#include <QObject>
#include <QList>
#include <QDate>

class ModelItem;

class ModelCompany : public QObject
{
    Q_OBJECT
public:
    ModelCompany(QObject *parent = 0);
    ~ModelCompany();

    void AddItem(ModelItem* i_model_item);
    void SetCompanyName(const QString& i_company_name);
    QString GetCompanyName() const;

    QList<ModelItem*> GetListOfItems() const;
    QList<QObject*> GetListOfObjectItems() const;

    QDate getStartPeriod() const;
    QDate getEndPeriod() const;

private:
    QDate m_period_start;
    QDate m_period_end;

    QString m_company_name;
    QList<ModelItem*> m_model;
    QList<QObject*> m_object_model;
};

#endif // MODELCOMPANY_H
