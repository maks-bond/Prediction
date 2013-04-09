#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <QVector>

class MathUtils
{
public:
    //same number of one bits(higher)
    static int Snoob(int i_x);
    static int GenerateMinimumNumberOfBits(int i_bits);
    static int GenerateMaximumNumberOfBits(int i_bits, int i_max_bit);
    static QVector<int> GenerateCombinationsOfOneBits(int i_bits, int i_max_bits);

    //Can be template
    static QVector<int> ApplyMaskForElements(const QVector<int>& i_elements, int i_mask);

private:
    MathUtils();
};

#endif // MATHUTILS_H
