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
    matrix.PushVariable(y);

    QVector<double> w;
    w<<1<<0;

    //y=x
    QTest::newRow("1")<<y<<matrix<<w;

    y.clear();
    matrix.Clear();
    Matrix::TVariable var;
    var<<1<<0<<2;
    matrix.PushVariable(var);
    var.clear();
    var<<-1<<1<<-1;

    w.clear();
    w<<1<<3<<2;
    //y=2+1*x1+3*x2
    QTest::newRow("2")<<y<<matrix<<w;
}

#undef private
