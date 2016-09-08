#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

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

// Q 5.3 ConvertBase
string convertBase(string origNumber, unsigned int srcBase, unsigned int targBase)
{
    string targBaseString;
    string deciBaseString;
    int decimalNumber;

    if (srcBase == targBase)
    {
        return origNumber;
    }

    // Part 1: Convert the origNumber to decimal
    int temp = 0;
    if (srcBase < 10)
    {
        for (int i = 0; i < origNumber.length(); i++)
        {
            temp += (origNumber[i] - '0') * (pow(srcBase, (origNumber.length() - 1) - i));
        }
    }
    else
    {
        for (int i = 0; i < origNumber.length(); i++)
        {
            if (origNumber[i] >= 'A' && origNumber[i] <= 'Z')
            {
                temp += (origNumber[i] - 'A' + 10) * (pow(srcBase, (origNumber.length() - 1) - i));
            }
            else
            {
                temp += (origNumber[i] - '0') * (pow(srcBase, (origNumber.length() - 1) - i));
            }

        }
    }

    decimalNumber = temp;
    deciBaseString = to_string(temp);

    // Part 2: Convert Decimal Number to Required base type.
    vector<char> vecTmpStr;
    int i = 0;
    while (temp != 0)
    {
        // If base is more than 9 then the number is Alpha Numeric
        int remainder = (temp % targBase);
        if (remainder > 9)
        {
            vecTmpStr.push_back(remainder + 'A' - 10);
        }
        else
        {
            vecTmpStr.push_back(remainder + '0');
        }

        temp = temp / targBase;
        i++;
    }
    
    // Reverse the String and store it back
    reverse(vecTmpStr.begin(), vecTmpStr.end());
    string tmp(vecTmpStr.begin(), vecTmpStr.end());
    targBaseString = tmp;

    return targBaseString;
}

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

    cout << "Convert Base: " << convertBase("FE12D", 16, 8) << endl;
    cout << endl;
    return 0;
}
