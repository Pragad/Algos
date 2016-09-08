#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;

class LRUCache
{
private:
    int _capacity;
    list<int> _lruList;
    unordered_map<int, list<int>* > _lruMap;

public:
    LRUCache(int capacity);
    int get(int key);
    void set(int key, int value);
};

LRUCache::LRUCache(int capacity) :
          _capacity(capacity),
          _lruList(capacity)
{ }

int
LRUCache::get(int key)
{
    return 0;
}

void
LRUCache::set(int key, int value)
{
    
}

int main()
{
    LRUCache 
    std::cout << "\n";
    return 0;
}
