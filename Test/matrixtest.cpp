#include "matrixtest.h"
#include "../matrix.h"

#include <QString>
#include <QtTest>

MatrixTest::MatrixTest()
{
}

void MatrixTest::TestGetOperations()
{
    QFETCH(int,col);
    QFETCH(int,observation_number);
    QFETCH(int,variable_number);
    QFETCH(Matrix::TVariable,variable);
    QFETCH(Matrix,matrix);

    QCOMPARE(variable,matrix.GetVariable(col));
    QCOMPARE(observation_number,matrix.GetObservationNumber());
    QCOMPARE(variable_number,matrix.GetVariablesNumber());

}


void MatrixTest::TestGetOperations_data()
{
    QTest::addColumn<int>("col");
    QTest::addColumn<int>("observation_number");
    QTest::addColumn<int>("variable_number");
    QTest::addColumn<Matrix::TVariable>("variable");
    QTest::addColumn<Matrix>("matrix");

    Matrix test;
    Matrix::TVariable var;

    var << 1 << 2 << 3;
    test.PushVariable(var);
    QTest::newRow("0") << 0 << 3 << 1 << var << test;

    var.clear();
    var << 4 << 5 << 6 ;
    test.PushVariable(var);
    QTest::newRow("1") << 1 << 3 << 2 << var << test;

    test.RemoveVariable(0);
    var.clear();
    var << 4 << 5 << 6;
    QTest::newRow("2") << 0 << 3 << 1 << var << test;

    var.clear();
    var << 7 << 8 << 9;
    test.PushVariable(var);
    test.RemoveVariable(1);
    var.clear();
    var << 4 << 5 << 6;
    QTest::newRow("3") << 0 << 3 << 1 << var << test;

    test = Matrix();
    var.clear();
    var << 1 << 2 << 3 << 4;
    test.PushVariable(var);
    QTest::newRow("4") << 0 << 4 << 1 << var << test;

    var.clear();
    var << 5 << 6 << 7 << 8;
    test.PushVariable(var);
    QTest::newRow("5") << 1 << 4 << 2 << var << test;

}

void MatrixTest::TestGetTimeSlice()
{
    QFETCH(int,n);
    QFETCH(Matrix,matrix);
    QFETCH(Matrix::TTimeSlice,time_slice);

    QCOMPARE(matrix.GetTimeSlice(n),time_slice);

}

void MatrixTest::TestGetTimeSlice_data()
{
    QTest::addColumn<int>("n");
    QTest::addColumn<Matrix>("matrix");
    QTest::addColumn<Matrix::TTimeSlice>("time_slice");

    Matrix test;
    Matrix::TVariable var;

    var << 1 << 2 << 3 << 4;
    test.PushVariable(var);

    var.clear();
    var << 5 << 6 << 7 << 8;
    test.PushVariable(var);

    var.clear();
    var << 9 << 10 << 11 << 12;
    test.PushVariable(var);

    Matrix::TTimeSlice time_slice;
    time_slice << 1 << 5 << 9;
    QTest::newRow("0") << 0 << test << time_slice;

    time_slice.clear();
    time_slice << 2 << 6 << 10;
    QTest::newRow("1") << 1 << test << time_slice;

    time_slice.clear();
    time_slice << 3 << 7 << 11;
    QTest::newRow("2") << 2 << test << time_slice;

    time_slice.clear();
    time_slice << 4 << 8 << 12;
    QTest::newRow("3") << 3 << test << time_slice;

    test.RemoveVariable(1);
    time_slice.clear();
    time_slice << 3 << 11;
    QTest::newRow("4") << 2 << test << time_slice;

    test.RemoveVariable(0);
    time_slice.clear();
    time_slice << 12;
    QTest::newRow("5") << 3 << test << time_slice;

}

void MatrixTest::TestTimeSliceFilter()
{
    QFETCH(Matrix,matrix);
    QFETCH(Matrix::TTimeSlice,time_slice);
    QFETCH(Matrix::TFilter,filter);
    QFETCH(int,i);

    QCOMPARE(time_slice,matrix.GetTimeSlice(i,filter));
}

void MatrixTest::TestTimeSliceFilter_data()
{
    QTest::addColumn<int>("i");
    QTest::addColumn<Matrix>("matrix");
    QTest::addColumn<Matrix::TTimeSlice>("time_slice");
    QTest::addColumn<Matrix::TFilter>("filter");

    Matrix test;
    Matrix::TVariable var;
    var << 1 << 2 << 3;
    test.PushVariable(var);
    var.clear();
    var << 4 << 5 << 6;
    test.PushVariable(var);
    var.clear();
    var << 7 << 8 << 9;
    test.PushVariable(var);

    Matrix::TTimeSlice time_slice;
    time_slice << 1 << 7;
    Matrix::TFilter filter;
    filter << 0 << 2 ;
    QTest::newRow("1") << 0 << test << time_slice << filter;

    time_slice.clear();
    time_slice << 2 << 5;
    filter.clear();
    filter << 0 << 1;
    QTest::newRow("2") << 1 << test << time_slice << filter;

    time_slice.clear();
    time_slice << 6 << 9;
    filter.clear();
    filter << 1 << 2;
    QTest::newRow("3") << 2 << test << time_slice << filter;
}

void MatrixTest::TestEmpty()
{
    QFETCH(bool,empty);
    QFETCH(Matrix,matrix);
    QFETCH(int,var_number);
    QFETCH(int,observation_number);

    QCOMPARE(empty,matrix.IsEmpty());
    QCOMPARE(var_number,matrix.GetVariablesNumber());
    QCOMPARE(observation_number,matrix.GetObservationNumber());

}

void MatrixTest::TestEmpty_data()
{
    QTest::addColumn<bool>("empty");
    QTest::addColumn<int>("var_number");
    QTest::addColumn<int>("observation_number");
    QTest::addColumn<Matrix>("matrix");

    Matrix test;

    QTest::newRow("0") << true << 0 << 0 <<  test;

    Matrix::TVariable var;
    var << 1 << 2;
    test.PushVariable(var);

    QTest::newRow("1") << false << 1 << 2 <<  test;

    test.RemoveVariable(0);
    QTest::newRow("2") << true << 0 << 0 << test;
}

void MatrixTest::TestData()
{
    QFETCH(int,n);
    QFETCH(QVector<double>,data);
    QFETCH(Matrix, matrix);

    double* raw_data = matrix.Data();
    QVector<double> c_data;
    for(int i=0;i<n;i++){
        c_data.push_back(raw_data[i]);
    }
    QCOMPARE(c_data,data);
}

void MatrixTest::TestData_data()
{
    QTest::addColumn<int>("n");
    QTest::addColumn<QVector<double> >("data");
    QTest::addColumn<Matrix>("matrix");

    Matrix test;
    Matrix::TVariable var;
    var << 1;
    test.PushVariable(var);
    QVector<double> data;
    data << 1;
    QTest::newRow("1") << 1 << data << test;

    test = Matrix();
    var.clear();
    var << 1 << 2;
    test.PushVariable(var);
    var.clear();
    var << 3 << 4;
    test.PushVariable(var);
    data.clear();
    data << 1 << 3 << 2 << 4;
    QTest::newRow("2") << 4 << data << test;

    test = Matrix();
    var.clear();
    var << 1 << 2 << 3;
    test.PushVariable(var);
    var.clear();
    var << 4 << 5 << 6;
    test.PushVariable(var);
    var.clear();
    var << 7 << 8 << 9;
    test.PushVariable(var);
    data.clear();
    data << 1 << 4 << 7 << 2 << 5 << 8 << 3 << 6 << 9;
    QTest::newRow("3") << 9 << data << test;

}
