#ifndef CONTROLLER_H
#define CONTROLLER_H

class QDir;
class QString;
class DataModel;
class AbstractGMDH;

class Controller
{
public:
    Controller();
    ~Controller();

    void Initialize(const QDir& i_dir);
    bool IsInitialized() const;

    const DataModel* GetDataModel() const;
    bool IsValidCompanyName(const QString& i_comp_name);

    double Forecast(QString i_company_name);

private:
    DataModel* mp_data_model;
    AbstractGMDH* mp_gmdh;
};

#endif // CONTROLLER_H
