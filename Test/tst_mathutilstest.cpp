#include <QString>
#include <QtTest>

#include "../mathutils.h"

class MathUtilsTest : public QObject
{
    Q_OBJECT
    
public:
    MathUtilsTest();
    
private Q_SLOTS:
    void SnoobTest();
    void SnoobTest_data();
};

MathUtilsTest::MathUtilsTest()
{
}

void MathUtilsTest::SnoobTest_data()
{
    QTest::addColumn<int>("snoob");
    QTest::addColumn<int>("result");

    QTest::newRow("3")<<3<<5;
    QTest::newRow("6")<<6<<9;
    QTest::newRow("11")<<11<<13;
    QTest::newRow("23")<<23<<27;
    QTest::newRow("24")<<24<<33;
    QTest::newRow("44")<<44<<49;
    QTest::newRow("46")<<46<<51;
}

void MathUtilsTest::SnoobTest()
{
    QFETCH(int, snoob);
    QFETCH(int, result);

    QCOMPARE(MathUtils::Snoob(snoob), result);
    //QVERIFY(MathUtils::Snoob(3) == 5);
}

QTEST_APPLESS_MAIN(MathUtilsTest)

#include "tst_mathutilstest.moc"
