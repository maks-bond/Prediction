#include "datamodeltest.h"

#include "matrix.h"
#include "datamodel.h"

#include <QTest>

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
}
