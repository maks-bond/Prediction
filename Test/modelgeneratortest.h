#ifndef MODELGENERATORTEST_H
#define MODELGENERATORTEST_H

#include <QObject>

class ModelGeneratorTest : public QObject
{
    Q_OBJECT

public:
    ModelGeneratorTest();

private Q_SLOTS:
    void SnoobTest();
    void SnoobTest_data();

    void GenerateMinimumNumberOfBitsTest();
    void GenerateMaximumNumberOfBitsTest();

    void GenerateCombinationsOfOneBitsTest();
    void GenerateCombinationsOfOneBitsTest_data();

    void ApplyMaskForElementsTest();
    void ApplyMaskForElementsTest_data();

    void GenerateBasicModelTest();
    void GenerateBasicModelTest_data();
};

#endif // MODELGENERATORTEST_H
