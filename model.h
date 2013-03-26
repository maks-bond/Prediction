#ifndef MODELFORECASTING_H
#define MODELFORECASTING_H

#include <QObject>
#include <QVector>

class ModelCompany;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
    ~Model();

    void AddCompany(ModelCompany* i_model_comopany);

    QVector<ModelCompany*> GetListOfCompanies() const;

    bool HasCompanies() const;

private:
    QVector<ModelCompany*> m_model;
};

#endif // MODELFORECASTING_H
