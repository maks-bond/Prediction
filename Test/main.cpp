#include <QCoreApplication>

#include <QTest>

#include "modelgeneratortest.h"
#include "datamodeltest.h"
#include "matrixtest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTest::qExec(new ModelGeneratorTest);
    QTest::qExec(new DataModelTest);
    QTest::qExec(new MatrixTest);
    return a.exec();
}
