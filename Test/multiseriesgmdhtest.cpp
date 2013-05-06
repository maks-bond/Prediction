#include "multiseriesgmdhtest.h"
#include <QTest>

#define protected public
#define private public

#include "multiseriesgmdh.h"
#include "matrix.h"
#include "forecastmodel.h"


MultiSeriesGMDHTest::MultiSeriesGMDHTest(QObject *parent) : QObject(parent)
{
}

void MultiSeriesGMDHTest::GenForecastModelData()
{
    QFETCH(Matrix,data);
    QFETCH(ForecastModel,model);
    QFETCH(MultiSeriesGMDH,gmdh);

    QCOMPARE(data,gmdh._GenForecastModelData(model));
}

void MultiSeriesGMDHTest::GenForecastModelData_data()
{
    QTest::addColumn<Matrix>("data");
    QTest::addColumn<ForecastModel>("model");
    QTest::addColumn<MultiSeriesGMDH>("gmdh");

    BasicModel basic_model;

    Component c;
    c << 0;
    basic_model << c;

    c.clear();
    c << 1;
    basic_model << c;

    c.clear();
    c << 0 << 1;
    basic_model << c;

    Matrix matrix;
    Matrix::TVariable v;
    v << 1 << 2 << 3;
    matrix.PushVariable(v);
    v.clear();
    v << 4 << 5 << 6;
    matrix.PushVariable(v);

    v.clear();
    v << 7 << 8 << 9;

    MultiSeriesGMDH algo;
    algo.m_basic_model = basic_model;
    algo.SetData(matrix,v);

    Matrix res;
    v.clear();
    v << 1 << 2 << 3;
    res.PushVariable(v);
    v.clear();
    v << 4 << 5 << 6;
    res.PushVariable(v);
    v.clear();
    v << 4 << 10 << 18;
    res.PushVariable(v);

    ForecastModel model;
    QVector<int> params;
    params << 0 << 1 << 2;
    model.SetParams(params);

    QTest::newRow("1") <<  res << model << algo;
}

#undef protected
#undef private
