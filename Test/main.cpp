#include <QCoreApplication>

#include <QTest>

#include "modelgeneratortest.h"
#include "datamodeltest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTest::qExec(new ModelGeneratorTest);
    QTest::qExec(new DataModelTest);
    return a.exec();
}
