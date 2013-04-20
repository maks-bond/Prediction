#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <QVector>

#include <stdexcept>

class MathUtils
{
public:
    //same number of one bits(higher)
    static int Snoob(int i_x);
    static int GenerateMinimumNumberOfBits(int i_bits);
    static int GenerateMaximumNumberOfBits(int i_bits, int i_max_bit);
    static QVector<int> GenerateCombinationsOfOneBits(int i_bits, int i_max_bits);
    static QVector<int> GetOneBitsIndexes(int i_n);

    template <typename Type>
    static QVector<Type> ApplyMaskForElements(const QVector<Type>& i_elements, int i_mask);

private:
    MathUtils();
};

template <typename Type>
QVector<Type> MathUtils::ApplyMaskForElements(const QVector<Type> &i_elements, int i_mask)
{
    if(i_mask < 0)
        throw std::logic_error("Bad number of bits");

    QVector<Type> result;

    for(int i = 0; i<=i_elements.size(); ++i)
    {
        if(i_mask&1)
            result.push_back(i_elements[i]);

        i_mask>>=1;
    }

    return result;
}

#endif // MATHUTILS_H
