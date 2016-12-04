#include <iostream>
#include <vector>
using namespace std;
/*
1. Implement a stack class (of integers) which supports the push() and pop() operations.
2. Implement a min() operation on this stack class to return the minimum value currently stored in the stack.
  - Implement this in O(1) constant time.
*/
class Stack
{
    public:
        void push(int num);
        int pop();
        int min();
        
    private:
        // Stack of numbers
        vector<int> _nums;
        
        // Second stack to support min numbers
        vector<int> _minNums;      
};

void
Stack::push(int num)
{
    _nums.push_back(num);
    
    // Update second stack for storing minimum numbers
    if (_minNums.empty())
    {
        _minNums.push_back(num);
        return; 
    }
    
    if (num < _minNums[_minNums.size() - 1])
    {
        _minNums.push_back(num);
    }
}


int
Stack::pop()
{
    // Calling pop on an empty stack
    if (_nums.empty())
    {
        return -1;
    }
    
    int tmpNum = _nums[_nums.size() - 1];
    _nums.pop_back();
    
    // Update second stack 
    if (tmpNum == _minNums[_minNums.size() - 1])
    {
        _minNums.pop_back();
    }    
    
    return tmpNum;
}

// Time Complexity: O(1)
int 
Stack::min()
{
    if (_minNums.empty())
    {
        return -1;
    }
    
    return (_minNums[_minNums.size() - 1]);
}


/*
Stack: 5, 7, 4, 8, 3, 9, 3, 2, 3
Min Stack: 5, 4, 3, 2
New number getting pushed min is less than the current minimum
*/
int main()
{
    Stack ob;
    ob.push(5);
    ob.push(7);
    ob.push(4);
    ob.push(8);
    ob.push(3);
    cout << "Pop: " << ob.pop() << endl;
    cout << "Min: " << ob.min() << endl;
    ob.push(1);
    ob.push(9);
    ob.push(3);
    ob.push(2);
    cout << "Pop: " << ob.pop() << endl;
    cout << "Min: " << ob.min() << endl;
    ob.push(3);
    cout << "Pop: " << ob.pop() << endl;
    cout << "Min: " << ob.min() << endl;
    
    
    return 0;
}


/*
Pop: 3
Min: 4
Pop: 2
Min: 1
Pop: 3
Min: 1
*/