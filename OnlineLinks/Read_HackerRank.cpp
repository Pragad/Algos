#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
5
1 6 10 8 4
*/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int numEntries;
    cin >> numEntries;
    cout << numEntries << endl;
    std::vector<int> vec{};
    vec.resize(numEntries);
    
    for (auto&& element : vec) {
        std::cin >> element;
    }
    std::reverse(vec.begin(), vec.end());

    for (auto itr = vec.crbegin(), end = vec.crend(); itr != end; ++itr) {
        cout << *itr << ", ";
    }
    
        
    return 0;
}

/*
abc, def, ghi
*/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    std::string numEntries;
    cin >> numEntries;
    cout << numEntries << endl;
    return 0;
}

/*
3
Peter
Me
Arxwwz
*/
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int numEntries;
    cin >> numEntries;
    cout << numEntries << endl;
    std::vector<std::string> vec{};
    vec.resize(numEntries);
    
    for (auto&& element : vec) {
        std::cin >> element;
    }
    std::reverse(vec.begin(), vec.end());

    for (auto itr = vec.crbegin(), end = vec.crend(); itr != end; ++itr) {
        cout << *itr << ", ";
    }
    return 0;
}
