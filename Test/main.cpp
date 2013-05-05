#include <QCoreApplication>

#include <QTest>

#include "forecastmodeltest.h"
#include "modelgeneratortest.h"
#include "datamodeltest.h"
#include "matrixtest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTest::qExec(new ModelGeneratorTest);
    QTest::qExec(new DataModelTest);
    QTest::qExec(new MatrixTest);
    QTest::qExec(new forecastmodeltest);
    return a.exec();
}
