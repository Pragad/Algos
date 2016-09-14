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
            _rangeKey = stRng;
            _rangeKey <<= sizeof(int);
            _rangeKey ^= enRng;
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

int main()
{
    int a = 5;
    int b = 7;
    signed long long c = a;
    c <<= sizeof(int);
    c ^= b;

    std::cout << sizeof(a) << "\n";
    std::cout << sizeof(b) << "\n";
    std::cout << sizeof(c) << "\n";
    std::cout << "\n";
    return 0;
}
