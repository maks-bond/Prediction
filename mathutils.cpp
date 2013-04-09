#include "mathutils.h"

#include <stdexcept>

// this function returns next higher number with same number of set bits as x.
int MathUtils::Snoob(int i_x)
{
    unsigned u_x = static_cast<unsigned>(i_x);
    unsigned rightOne;
    unsigned nextHigherOneBit;
    unsigned rightOnesPattern;

    unsigned next = 0;

    if(u_x)
    {

    // right most set bit
    rightOne = u_x & -(signed)u_x;

    // reset the pattern and set next higher bit
    // left part of x will be here
    nextHigherOneBit = u_x + rightOne;

    // nextHigherOneBit is now part [D] of the above explanation.

    // isolate the pattern
    rightOnesPattern = u_x ^ nextHigherOneBit;

    // right adjust pattern
    rightOnesPattern = (rightOnesPattern)/rightOne;

    // correction factor
    rightOnesPattern >>= 2;

    // rightOnesPattern is now part [A] of the above explanation.

    // integrate new pattern (Add [D] and [A])
    next = nextHigherOneBit | rightOnesPattern;
    }

    return next;
}

int MathUtils::GenerateMinimumNumberOfBits(int i_bits)
{
    if(i_bits<=0)
        throw std::logic_error("Bad number of bits");

    return (1<<i_bits)-1;
}

int MathUtils::GenerateMaximumNumberOfBits(int i_bits, int i_max_bit)
{
    if(i_bits > i_max_bit || i_bits <= 0)
        throw std::logic_error("Bad number of bits");

    return GenerateMinimumNumberOfBits(i_bits)<<(i_max_bit - i_bits);
}

MathUtils::MathUtils()
{
}
