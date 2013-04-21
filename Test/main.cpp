#include <QCoreApplication>

#include <QTest>

#include "modelgeneratortest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTest::qExec(new ModelGeneratorTest);
    return a.exec();
}
