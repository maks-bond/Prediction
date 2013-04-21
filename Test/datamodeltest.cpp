#include "datamodeltest.h"

#include "matrix.h"
#include "datamodel.h"
#include "datacompany.h"

#include <QTest>

#include <stdexcept>

namespace
{
    DataModel Generate1_1DataModel(double i_price)
    {
        DataModel data_model;
        DataCompany data_company;
        data_company.PushPrice(i_price);
        data_company.SetStartDate(QDate::currentDate());
        data_company.SetCompanyName("Apple");
        data_model.SetStartDate(QDate::currentDate());
        data_model.AddCompanyData(data_company);
        return data_model;
    }

    DataModel GenerateWrongDataModel(QVector<double> i_prices)
    {
        if(i_prices.size() != 3)
            throw std::logic_error("Must be 3 prices");

        DataModel data_model;
        DataCompany data_company;
        data_company.PushPrice(i_prices[0]);
        data_company.SetStartDate(QDate::currentDate());
        data_company.SetCompanyName("Apple");
        data_model.SetStartDate(QDate::currentDate());
        data_model.AddCompanyData(data_company);
        DataCompany data_company2;
        data_company2.SetStartDate(QDate::currentDate());
        data_company2.SetCompanyName("IBM");
        data_company2.PushPrice(i_prices[1]);
        data_company2.PushPrice(i_prices[2]);
        data_model.AddCompanyData(data_company2);
        return data_model;
    }

    DataModel Generate2_2DataModel(QVector<double> i_prices)
    {
        if(i_prices.size() != 4)
            throw std::logic_error("Must be 3 prices");

        DataModel data_model;
        DataCompany data_company;
        data_company.PushPrice(i_prices[0]);
        data_company.PushPrice(i_prices[1]);
        data_company.SetStartDate(QDate::currentDate());
        data_company.SetCompanyName("Apple");
        data_model.SetStartDate(QDate::currentDate());
        data_model.AddCompanyData(data_company);
        DataCompany data_company2;
        data_company2.SetStartDate(QDate::currentDate());
        data_company2.SetCompanyName("IBM");
        data_company2.PushPrice(i_prices[2]);
        data_company2.PushPrice(i_prices[3]);
        data_model.AddCompanyData(data_company2);
        return data_model;
    }
}

DataModelTest::DataModelTest(QObject *parent) :
    QObject(parent)
{
}

void DataModelTest::GetRawDataTest()
{
    QFETCH(DataModel, data_model);
    QFETCH(Matrix, result);

    QCOMPARE(data_model.GetRawData(), result);
}

void DataModelTest::GetRawDataTest_data()
{
    QTest::addColumn<DataModel>("data_model");
    QTest::addColumn<Matrix>("result");

    DataModel data_model;
    Matrix matrix;

    QTest::newRow("Test1")<<data_model<<matrix;

    matrix.PushVariable(Matrix::TVariable(1, 1.0));

    QTest::newRow("Test2")<<Generate1_1DataModel(1.0)<<matrix;
    //Test must generate an exception
    //QVector<double> prices(3, 1.0);
    //matrix.PushVariable(Matrix::TVariable(2, 1.0));
    //QTest::newRow("Test3")<<GenerateWrongDataModel(prices)<<matrix;

    QVector<double> prices;
    prices<<1.0<<2.0<<3.0<<4.0;
    Matrix matrix2;
    Matrix::TVariable variable;
    variable<<1.0<<2.0;
    matrix2.PushVariable(variable);
    variable.clear();
    variable<<3.0<<4.0;
    matrix2.PushVariable(variable);

    QTest::newRow("Test4")<<Generate2_2DataModel(prices)<<matrix2;
}

void DataModelTest::IsValidTest()
{
    QFETCH(DataModel, data_model);
    QFETCH(bool, result);

    QCOMPARE(data_model.IsValid(), result);
}

void DataModelTest::IsValidTest_data()
{
    QTest::addColumn<DataModel>("data_model");
    QTest::addColumn<bool>("result");

    DataModel data_model;
    QTest::newRow("Test1")<<data_model<<false;
    QTest::newRow("Test2")<<Generate1_1DataModel(1.0)<<true;
    data_model.SetStartDate(QDate::currentDate());
    QTest::newRow("Test3")<<data_model<<false;
    DataCompany data_company;
    data_company.SetStartDate(QDate::currentDate());
    data_company.SetCompanyName("Apple");
    data_company.PushPrice(1.0);
    data_model.AddCompanyData(data_company);
    QTest::newRow("Test4")<<data_model<<true;
}

void DataModelTest::GetVariableTest()
{
    QFETCH(DataModel, data_model);
    QFETCH(QString, company_name);
    QFETCH(Matrix::TVariable, result);

    QCOMPARE(data_model.GetVariable(company_name), result);
}

void DataModelTest::GetVariableTest_data()
{
    QTest::addColumn<DataModel>("data_model");
    QTest::addColumn<QString>("company_name");
    QTest::addColumn<Matrix::TVariable>("result");

    QTest::newRow("Test1")<<Generate1_1DataModel(1.0)<<QString("Apple")<<Matrix::TVariable(1, 1.0);
    QVector<double> prices;
    prices<<1.0<<2.0<<3.0<<4.0;
    Matrix::TVariable var1;
    var1<<1.0<<2.0;
    Matrix::TVariable var2;
    var2<<3.0<<4.0;
    QTest::newRow("Test2")<<Generate2_2DataModel(prices)<<QString("Apple")<<var1;
    QTest::newRow("Test3")<<Generate2_2DataModel(prices)<<QString("IBM")<<var2;
}

void DataModelTest::GetRawDataExceptTest()
{
    QFETCH(DataModel, data_model);
    QFETCH(QString, company_name);
    QFETCH(Matrix, result);

    QCOMPARE(data_model.GetRawDataExcept(company_name), result);
}

void DataModelTest::GetRawDataExceptTest_data()
{
    QTest::addColumn<DataModel>("data_model");
    QTest::addColumn<QString>("company_name");
    QTest::addColumn<Matrix>("result");

    QVector<double> prices;
    prices<<1.0<<2.0<<3.0<<4.0;
    DataModel data_model = Generate2_2DataModel(prices);
    Matrix matrix;
    Matrix::TVariable var1;
    var1<<1.0<<2.0;
    Matrix::TVariable var2;
    var2<<3.0<<4.0;
    matrix.PushVariable(var1);
    QTest::newRow("Test1")<<data_model<<"IBM"<<matrix;
    matrix.Clear();
    matrix.PushVariable(var2);
    QTest::newRow("Test2")<<data_model<<"Apple"<<matrix;
    data_model = Generate1_1DataModel(1.0);
    QTest::newRow("Test3")<<data_model<<"Apple"<<Matrix();
}
