#ifndef MATHUTILS_H
#define MATHUTILS_H

class MathUtils
{
public:
    //same number of one bits(higher)
    static int Snoob(int i_x);
    static int GenerateMinimumNumberOfBits(int i_bits);
    static int GenerateMaximumNumberOfBits(int i_bits, int i_max_bit);

private:
    MathUtils();
};

#endif // MATHUTILS_H
