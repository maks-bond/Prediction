#include "forecastmodeltest.h"

#define private public

#include "forecastmodel.h"
#include "matrix.h"

#include <QTest>

#include <cmath>
#include <stdexcept>

namespace
{
    const double g_eps = 1e-2;

    bool DoubleEqual(double a, double b)
    {
        return fabs(a-b) < g_eps;
    }

    bool DoubleVectorEqual(const QVector<double>& i_a, const QVector<double>& i_b)
    {
        if(i_a.size() != i_b.size())
            throw std::logic_error("bad!!");

        for(int i = 0; i<i_a.size(); ++i)
            if(!DoubleEqual(i_a[i], i_b[i]))
                return false;

        return true;
    }
}
forecastmodeltest::forecastmodeltest(QObject *parent) :
    QObject(parent)
{
}

void forecastmodeltest::SetUpTest()
{
    QFETCH(Matrix::TVariable, y);
    QFETCH(Matrix, matrix);
    QFETCH(QVector<double>, w_result);

    ForecastModel model;
    model.SetUp(y, matrix);

    QCOMPARE(DoubleVectorEqual(model.m_w, w_result), true);
}

void forecastmodeltest::SetUpTest_data()
{
    QTest::addColumn<Matrix::TVariable>("y");
    QTest::addColumn<Matrix>("matrix");
    QTest::addColumn<QVector<double> >("w_result");

    Matrix::TVariable y;
    y<<0<<1;

    Matrix matrix;
    Matrix::TVariable var;
    var<<0<<1;
    matrix.PushVariable(var);

    QVector<double> w;
    w<<0<<1;

    //y=x
    QTest::newRow("1")<<y<<matrix<<w;

    y.clear();
    y<<0<<5<<1;
    matrix.Clear();
    var.clear();
    var<<1<<0<<2;
    matrix.PushVariable(var);
    var.clear();
    var<<-1<<1<<-1;
    matrix.PushVariable(var);

    w.clear();
    w<<2<<1<<3;
    //y=2+1*x1+3*x2
    QTest::newRow("2")<<y<<matrix<<w;

    y.clear();
    y<<0<<-3<<-1<<-2;
    var.clear();
    matrix.Clear();
    var<<3<<6<<4<<5;
    matrix.PushVariable(var);
    w.clear();
    w<<3<<-1;
    //y=3-1*x(From Udacity:) )
    QTest::newRow("3")<<y<<matrix<<w;

    y.clear();
    var.clear();
    matrix.Clear();
    w.clear();
    y<<2<<5<<5<<8;
    var<<2<<4<<6<<8;
    matrix.PushVariable(var);
    w<<0.5<<0.9;
    //y=0.5+0.9(From Udacity:) )
    QTest::newRow("4")<<y<<matrix<<w;

    y.clear();
    var.clear();
    matrix.Clear();
    w.clear();
    y<<0<<1<<2;
    var<<0<<1<<2;
    w<<0<<1;
    matrix.PushVariable(var);

    QTest::newRow("5")<<y<<matrix<<w;
}

void forecastmodeltest::OperatorEqualTest()
{
    QFETCH(ForecastModel, one);
    QFETCH(ForecastModel, two);
    QFETCH(bool, result);

    QCOMPARE(one==two, result);
}

void forecastmodeltest::OperatorEqualTest_data()
{
    QTest::addColumn<ForecastModel>("one");
    QTest::addColumn<ForecastModel>("two");
    QTest::addColumn<bool>("result");

    QVector<int> vars;
    vars<<0<<1;
    QVector<int> vars2;
    vars2<<0;

    ForecastModel one(vars);
    ForecastModel two(vars);

    QTest::newRow("1")<<one<<two<<true;
    two.SetParams(vars2);
    QTest::newRow("2")<<one<<two<<false;

    two.SetParams(vars);

    Matrix::TVariable y;
    y<<0<<1;

    Matrix matrix;
    matrix.PushVariable(y);

    one.SetUp(y, matrix);
    QTest::newRow("3")<<one<<two<<false;
    y<<2;
    matrix.Clear();
    matrix.PushVariable(y);
    two.SetUp(y, matrix);

    QTest::newRow("4")<<one<<two<<true;
}

void forecastmodeltest::OperatorPlusTest()
{
    QFETCH(ForecastModel, one);
    QFETCH(ForecastModel, two);
    QFETCH(ForecastModel, res);

    QCOMPARE(one+two, res);
}

void forecastmodeltest::OperatorPlusTest_data()
{
    QTest::addColumn<ForecastModel>("one");
    QTest::addColumn<ForecastModel>("two");
    QTest::addColumn<ForecastModel>("res");

    QVector<int> vars1;
    QVector<int> vars2;
    QVector<int> vars3;
    QVector<int> varsres1;
    QVector<int> varsres2;
    QVector<int> varsres3;
    QVector<int> varsres4;
    vars1<<0<<1;
    vars2<<2<<3;
    vars3<<1<<2;
    varsres1<<0<<1<<2<<3;
    varsres2<<0<<0<<1<<1;
    varsres3<<0<<1<<1<<2;
    varsres4<<1<<2<<2<<3;
    ForecastModel a(vars1);
    ForecastModel b(vars2);
    ForecastModel c(vars3);

    ForecastModel res1(varsres1);
    ForecastModel res2(varsres2);
    ForecastModel res3(varsres3);
    ForecastModel res4(varsres4);

    QTest::newRow("1")<<a<<b<<res1;
    QTest::newRow("2")<<a<<a<<res2;
    QTest::newRow("3")<<a<<c<<res3;
    QTest::newRow("4")<<b<<c<<res4;
    QTest::newRow("5")<<ForecastModel()<<ForecastModel()<<ForecastModel();
}

void forecastmodeltest::EvaluateTest()
{
    QFETCH(ForecastModel, model);
    QFETCH(QVector<double>, vals);
    QFETCH(double, res);

    QCOMPARE(model.Evaluate(vals), res);
}

void forecastmodeltest::EvaluateTest_data()
{
    QTest::addColumn<ForecastModel>("model");
    QTest::addColumn<QVector<double> >("vals");
    QTest::addColumn<double>("res");

    ForecastModel model;
    Matrix::TVariable y;
    y<<0<<1;

    Matrix matrix;
    matrix.PushVariable(y);
    model.SetUp(y, matrix);

    QVector<double> vals;
    vals<<5.0;

    double res = 5;

    QTest::newRow("1")<<model<<vals<<res;

    Matrix::TVariable var;
    y.clear();
    y<<0<<5<<1;
    matrix.Clear();
    var.clear();
    var<<1<<0<<2;
    matrix.PushVariable(var);
    var.clear();
    var<<-1<<1<<-1;
    matrix.PushVariable(var);

    //y=2+1*x1+3*x2
    model.SetUp(y, matrix);

    vals.clear();
    vals<<1<<3;

    QTest::newRow("2")<<model<<vals<<12.0;
}

#undef private

