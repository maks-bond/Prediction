#ifndef CONTROLLER_H
#define CONTROLLER_H

class QDir;

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

    double Forecast(int i_company_index);

private:
    DataModel* mp_data_model;
    AbstractGMDH* mp_gmdh;
};

#endif // CONTROLLER_H