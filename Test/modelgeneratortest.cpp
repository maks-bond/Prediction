#include "modelgeneratortest.h"

#include <QString>
#include <QtTest>

#define private public

#include "../modelgenerator.h"

ModelGeneratorTest::ModelGeneratorTest()
{
}

void ModelGeneratorTest::SnoobTest_data()
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

void ModelGeneratorTest::SnoobTest()
{
    QFETCH(int, snoob);
    QFETCH(int, result);

    QCOMPARE(ModelGenerator::Snoob(snoob), result);
    //QVERIFY(ModelGenerator::Snoob(3) == 5);
}

void ModelGeneratorTest::GenerateMinimumNumberOfBitsTest()
{
    QVERIFY(ModelGenerator::GenerateMinimumNumberOfBits(1) == 1);
    QVERIFY(ModelGenerator::GenerateMinimumNumberOfBits(2) == 3);
}

void ModelGeneratorTest::GenerateMaximumNumberOfBitsTest()
{
    QVERIFY(ModelGenerator::GenerateMaximumNumberOfBits(2, 4) == 12);
    QVERIFY(ModelGenerator::GenerateMaximumNumberOfBits(2, 2) == 3);
    QVERIFY(ModelGenerator::GenerateMaximumNumberOfBits(1, 4) == 8);
}

void ModelGeneratorTest::GenerateCombinationsOfOneBitsTest()
{
    QFETCH(int, bits);
    QFETCH(int, max_bits);
    QFETCH(QVector<int>, result);

    QCOMPARE(ModelGenerator::GenerateCombinationsOfOneBits(bits, max_bits), result);
}

void ModelGeneratorTest::GenerateCombinationsOfOneBitsTest_data()
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

void ModelGeneratorTest::ApplyMaskForElementsTest()
{
    QFETCH(QVector<int>, elements);
    QFETCH(int, bits);
    QFETCH(QVector<int>, result);

    QCOMPARE(ModelGenerator::ApplyMaskForElements(elements, bits), result);
}

void ModelGeneratorTest::ApplyMaskForElementsTest_data()
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

void ModelGeneratorTest::GenerateBasicModelTest()
{
    QFETCH(int, number_of_companies);
    QFETCH(int, max_generation_length);
    QFETCH(BasicModel, result);

    QCOMPARE(ModelGenerator::GenerateBasicModel(number_of_companies, max_generation_length), result);
}

void ModelGeneratorTest::GenerateBasicModelTest_data()
{
    QTest::addColumn<int>("number_of_companies");
    QTest::addColumn<int>("max_generation_length");
    QTest::addColumn<BasicModel>("result");

    BasicModel result;
    result.push_back(QVector<int>(1, 0));
    result.push_back(QVector<int>(1, 1));
    QVector<int> comp3;
    comp3.push_back(0);
    comp3.push_back(1);
    result.push_back(comp3);

    QTest::newRow("Test1")<<2<<2<<result;
}

#undef private
