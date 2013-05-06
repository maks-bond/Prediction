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
}

#undef private
