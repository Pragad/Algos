#include <iostream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <climits>              // INT_MAX, INT_MIN, numeric_limits

#define MASK 0x00000000ffffffff

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
            _rangeKey = stRng;
            _rangeKey = _rangeKey & (MASK);

            // 1 Byte = 8 bits. So multiply the size by 8
            _rangeKey <<= (sizeof(int) * 8);
            _rangeKey ^= (enRng & MASK);
        }

        signed long long getRangeKey() { return _rangeKey; }
    };

    std::vector<Range> _rangeList;
    std::unordered_map<signed long long, uint64_t> _rangeMap;

public:
    bool isRangeValid(int stRng, int enRng);
    bool addRange(int stRng, int enRng);
    bool queryRange(int stRng, int enRng);
    bool deleteRange(int stRng, int enRng);
    void printRanges();
    void printMap();
};

bool 
RangeOps::isRangeValid(int stRng, int enRng)
{
    // return (stRng <= enRng);
    return true;
}

bool
RangeOps::addRange(int stRng, int enRng)
{

    if (isRangeValid(stRng, enRng))
    {
        Range ob(stRng, enRng);

        // Check if the Range is present already
        // If the Range is already present then return false to indicate the the element
        // did not get added
        auto itr = _rangeMap.find(ob.getRangeKey());
        if (itr != _rangeMap.end())
        {
            return false;
        }

        _rangeList.push_back(ob);
        _rangeMap[ob.getRangeKey()] = _rangeList.size() - 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool
RangeOps::queryRange(int stRng, int enRng)
{
    if (isRangeValid(stRng, enRng))
    {
        Range ob(stRng, enRng);

        // Check if the Range is present already
        auto itr = _rangeMap.find(ob.getRangeKey());
        if (itr != _rangeMap.end())
        {
            return true;
        }
    }

    return false;
}

bool
RangeOps::deleteRange(int stRng, int enRng)
{
    if (isRangeValid(stRng, enRng))
    {
        Range ob(stRng, enRng);

        // If the Range is not present then return false to indicate the the element
        // is not present in our list
        auto itr = _rangeMap.find(ob.getRangeKey());
        if (itr == _rangeMap.end())
        {
            return false;
        }

        // Store the last element in a temp variable
        Range tmp = _rangeList[_rangeList.size() - 1];

        // Push the last element to the position where element should be deleted
        _rangeList[itr->second] = tmp;

        _rangeMap[tmp.getRangeKey()] = itr->second;

        // Erase the last element from the vector as well as from the map
        _rangeList.pop_back();
        _rangeMap.erase(itr->first);

        return true;
    }
    else
    {
        return false;
    }
}

void
RangeOps::printRanges()
{
    std::cout << "\n\nRanges List\n";
    for (auto item : _rangeList)
    {
        std::cout << item._startRange << " : " << item._endRange << " : " << item._rangeKey << "\n";
        std::bitset<64> s(item._startRange);
        std::bitset<64> e(item._endRange);
        std::bitset<64> k(item._rangeKey);
        std::cout << s << " : " << e << " : " << k << "\n";
    }
    std::cout << "\n";
}

void
RangeOps::printMap()
{
    std::cout << "\n\nRanges Map\n";
    for (auto itr = _rangeMap.begin(); itr != _rangeMap.end(); itr++)
    {
        std::cout << itr->first << " : " << itr->second << "\n";
    }
    std::cout << "\n";
}

int main()
{
    int a1 = 5;
    int b1 = 10;

    int a2 = -5;
    int b2 = -7;

    int a3 = 1;
    int b3 = 10;

    int a4 = -15;
    int b4 = -20;

    int a5 = 10;
    int b5 = 30;

    RangeOps ob;
    std::cout << "AR 1: " << ob.addRange(a1, b1) << "\n";
    std::cout << "AR 2: " << ob.addRange(a2, b2) << "\n";
    std::cout << "AR 3: " << ob.addRange(a3, b3) << "\n";
    ob.printRanges();
    ob.printMap();

    std::cout << "QR 1: " << ob.queryRange(a1, b1) << "\n";
    std::cout << "QR 2: " << ob.queryRange(a2, b1) << "\n";
    std::cout << "QR 3: " << ob.queryRange(a2, b2) << "\n";

    std::cout << "DR 1: " << ob.deleteRange(a1, b2) << "\n";
    std::cout << "DR 2: " << ob.deleteRange(a1, b1) << "\n";
    std::cout << "DR 3: " << ob.deleteRange(a2, b2) << "\n";
    ob.printRanges();
    ob.printMap();

    std::cout << "AR 4: " << ob.addRange(a2, b2) << "\n";
    std::cout << "AR 5: " << ob.addRange(a4, b4) << "\n";
    std::cout << "AR 6: " << ob.addRange(a5, b5) << "\n";
    ob.printRanges();
    ob.printMap();

    std::cout << "DR 4: " << ob.deleteRange(a1, b1) << "\n";
    std::cout << "DR 5: " << ob.deleteRange(a2, b2) << "\n";
    ob.printRanges();
    ob.printMap();

    return 0;
}
