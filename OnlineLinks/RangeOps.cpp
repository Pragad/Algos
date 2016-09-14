#include <iostream>
#include <vector>
#include <unordered_map>

class RangeOps
{
private:

    // Inner Class
    class Range
    {
    public:
        int _startRange;
        int _endRange;
        signed long long _rangeKey;

        Range(int stRng, int enRng) : _startRange(stRng),
                                      _endRange(enRng)
        {
            // Mask is used to clear the upper four bits in a Signed Int
            // Say Start Range  = -5 (1111 1011)
            //     End Range    = -7 (1111 1001)
            //     Key Should be= 1011 1001
            //
            // 1. Copy startRange to Key
            // 2. Do a bitwise & to clear the upper four bits
            // 3. Do a shift to accomodate space for EndRange
            // 4. EndRange Bitwise & MASK will clear the upper four bits
            // 5. Do an XOR of above with rangekey
            int MASK = 0x0f;
            _rangeKey = stRng;
            _rangeKey = _rangeKey & MASK;

            _rangeKey <<= sizeof(int);
            _rangeKey ^= (enRng & MASK);
        }

        signed long long getRangeKey() { return _rangeKey; }
    };

    std::vector<Range> _rangeList;
    std::unordered_map<signed long long, uint64_t> _rangeMap;

public:
    bool addRange(int stRng, int enRng);
    bool queryRange(int stRng, int enRng);
    bool deleteRange(int stRng, int enRng);
};

bool
RangeOps::addRange(int stRng, int enRng)
{
    Range ob(stRng, enRng);
    auto itr = _rangeMap.find(ob.getRangeKey());

    if (itr == _rangeMap.end())
    {
        _rangeList.push_back(ob);
    }
}

int main()
{
    int a = 5;
    int b = 7;
    signed long long c = a;

    RangeOps ob;
    ob.addRange(a, b);

    std::cout << sizeof(a) << "\n";
    std::cout << sizeof(b) << "\n";
    std::cout << sizeof(c) << "\n";
    std::cout << "\n";
    return 0;
}
