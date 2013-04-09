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

    void GenerateMinimumNumberOfBitsTest();
    void GenerateMaximumNumberOfBitsTest();

    void GenerateCombinationsOfOneBitsTest();
    void GenerateCombinationsOfOneBitsTest_data();

    void ApplyMaskForElementsTest();
    void ApplyMaskForElementsTest_data();
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

void MathUtilsTest::GenerateMinimumNumberOfBitsTest()
{
    QVERIFY(MathUtils::GenerateMinimumNumberOfBits(1) == 1);
    QVERIFY(MathUtils::GenerateMinimumNumberOfBits(2) == 3);
}

void MathUtilsTest::GenerateMaximumNumberOfBitsTest()
{
    QVERIFY(MathUtils::GenerateMaximumNumberOfBits(2, 4) == 12);
    QVERIFY(MathUtils::GenerateMaximumNumberOfBits(2, 2) == 3);
    QVERIFY(MathUtils::GenerateMaximumNumberOfBits(1, 4) == 8);
}

void MathUtilsTest::GenerateCombinationsOfOneBitsTest()
{
    QFETCH(int, bits);
    QFETCH(int, max_bits);
    QFETCH(QVector<int>, result);

    QCOMPARE(MathUtils::GenerateCombinationsOfOneBits(bits, max_bits), result);
}

void MathUtilsTest::GenerateCombinationsOfOneBitsTest_data()
{
    QTest::addColumn<int>("bits");
    QTest::addColumn<int>("max_bits");
    QTest::addColumn<QVector<int> >("result");

    QVector<int> test1;// 1 2
    test1.push_back(1);
    test1.push_back(2);
    QTest::newRow("Test1")<<1<<2<<test1;

    QVector<int> test2;// 1 2 4
    test2.push_back(1);
    test2.push_back(2);
    test2.push_back(4);

    QTest::newRow("Test2")<<1<<3<<test2;

    QVector<int> test3;//3 5 6 9 10 12
    test3.push_back(3);
    test3.push_back(5);
    test3.push_back(6);
    test3.push_back(9);
    test3.push_back(10);
    test3.push_back(12);
    QTest::newRow("Test3")<<2<<4<<test3;
}

void MathUtilsTest::ApplyMaskForElementsTest()
{
    QFETCH(QVector<int>, elements);
    QFETCH(int, bits);
    QFETCH(QVector<int>, result);

    QCOMPARE(MathUtils::ApplyMaskForElements(elements, bits), result);
}

void MathUtilsTest::ApplyMaskForElementsTest_data()
{
    QTest::addColumn<QVector<int> >("elements");
    QTest::addColumn<int>("bits");
    QTest::addColumn<QVector<int> >("result");

    QVector<int> test1;// 1 2
    test1.push_back(1);
    test1.push_back(2);

    QVector<int> result1;// empty

    QVector<int> result2;// 1
    result2.push_back(1);

    QVector<int> result3;// 2
    result3.push_back(2);

    QVector<int> result4;// 1 2
    result4.push_back(1);
    result4.push_back(2);

    QVector<int> test2;// 1 2 3
    test2.push_back(1);
    test2.push_back(2);
    test2.push_back(3);

    QVector<int> result5;// 1 3
    result5.push_back(1);
    result5.push_back(3);

    QVector<int> result6;// 1 2 3
    result6.push_back(1);
    result6.push_back(2);
    result6.push_back(3);

    QTest::newRow("Test1")<<test1<<0<<result1;
    QTest::newRow("Test2")<<test1<<1<<result2;
    QTest::newRow("Test3")<<test1<<2<<result3;
    QTest::newRow("Test4")<<test1<<3<<result4;
    QTest::newRow("Test5")<<test2<<5<<result5;
    QTest::newRow("Test6")<<test2<<7<<result6;
}

QTEST_APPLESS_MAIN(MathUtilsTest)

#include "tst_mathutilstest.moc"
