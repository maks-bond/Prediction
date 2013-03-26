#ifndef MODELCOMPANY_H
#define MODELCOMPANY_H

#include <QObject>
#include <QList>

class ModelItem;

class ModelCompany : public QObject
{
    Q_OBJECT
public:
    ModelCompany(QObject *parent = 0);
    ~ModelCompany();

    void AddItem(ModelItem* i_model_item);
    void SetCompanyName(const QString& i_company_name);

    QList<ModelItem*> GetListOfItems() const;
    QList<QObject*> GetListOfObjectItems() const;

private:
    QString m_company_name;
    QList<ModelItem*> m_model;
    QList<QObject*> m_object_model;
};

#endif // MODELCOMPANY_H
