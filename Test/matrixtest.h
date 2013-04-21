#ifndef MATRIXTEST_H
#define MATRIXTEST_H

#include <QObject>

class MatrixTest : public QObject
{
    Q_OBJECT

public:
    MatrixTest();

private slots :
    void TestGetOperations();
    void TestGetOperations_data();

    void TestGetTimeSlice();
    void TestGetTimeSlice_data();

    void TestTimeSliceFilter();
    void TestTimeSliceFilter_data();

    void TestEmpty();
    void TestEmpty_data();

    void TestData();
    void TestData_data();

};

#endif // MATRIXTEST_H
