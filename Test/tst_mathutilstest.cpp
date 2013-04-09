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
};

MathUtilsTest::MathUtilsTest()
{
}

void MathUtilsTest::SnoobTest()
{
    QVERIFY(MathUtils::Snoob(1, 4) == 5);
}

QTEST_APPLESS_MAIN(MathUtilsTest)

#include "tst_mathutilstest.moc"
