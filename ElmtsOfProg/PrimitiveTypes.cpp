#include <iostream>
using namespace std;

#ifdef _WIN32
typedef char 	                int8_t;
typedef unsigned char 	        uint8_t;
typedef unsigned short int 	    uint16_t;
typedef unsigned int 	        uint32_t;
typedef unsigned long long int 	uint64_t;
#else
#include <stdint.h>
#endif


// Q: 5.1 Compute the Parity of a number
bool computeParity(uint64_t number)
{
    cout << number << endl;
    uint32_t count = 0;
    while (number)
    {
        // number & number - 1 eliminates the lowest set bits
        number = number & (number - 1);
        count++;
    }

    // Instead we could have used,
    // result ^= 1;
    return (count % 2);
}

// Q: 5.2 Compute x/y using +, - and shift operators
uint32_t numDivision(int x, int y)
{
    if (x < y)
    {
        return 0;
    }

    uint32_t quot = 0;
    while ((x-y) >= 0)
    {
        x -= y;
        quot++;
    }

    return quot;
}

// http://stackoverflow.com/questions/5386377/division-without-using
// https://www.youtube.com/watch?v=S5tD47NZx7w
// http://stackoverflow.com/questions/5284898/implement-division-with-bit-wise-operator?lq=1
uint32_t numDivisionOpt(int numerator, int denominator)
{
    int tmpDen = denominator;
    uint32_t quotient = 0;
    uint32_t current = 1;

    if (numerator < denominator)
    {
        return 0;
    }

    if (numerator == denominator)
    {
        return 1;
    }

    // If we are here, numerator is greater than denominator and quotient will be at least
    // 1.
    // Shift left so that we align the Left most bits of the numerator and denominator.
    while (numerator >= tmpDen)
    {
        tmpDen <<= 1;
        current <<= 1;
    }

    // Shift once to Right to overcome the extra shift that would have happened in the 
    // above loop.
    tmpDen >>= 1;
    current >>= 1;

    while (current != 0)
    {
        if (numerator >= tmpDen)
        {
            numerator -= tmpDen;
            tmpDen >>= 1;

            quotient += current;
            // IMP: This can be |=
            //quotient |= current;
        }

        tmpDen >>= 1;
        current >>= 1;
    }

    // Remainder will be stored in "numerator"
    return quotient;
}

// Q: 5.2b Find REMAINDER without using % operator.
// http://stackoverflow.com/questions/5189631/how-can-i-take-mod-of-a-number-in-assembly-in-motorola-m6800/5189800#5189800


int main()
{
    uint64_t longNum = 5;
    cout << "Parity: " << computeParity(longNum) << endl;
    cout << "Divide: " << numDivision(8, 3) << endl;
    cout << "Divide: " << numDivision(16, 3) << endl;
    cout << "Divide: " << numDivision(18, 3) << endl;
    cout << "Divide Opt: " << numDivision(8, 3) << endl;
    cout << "Divide Opt: " << numDivision(16, 3) << endl;
    cout << "Divide Opt: " << numDivision(18, 3) << endl;


    cout << endl;
    return 0;
}

