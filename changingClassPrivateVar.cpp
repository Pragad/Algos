// Using a Reference to a Pointer.
// This program helps to understand how to obtain a Class's
// private variable by passing a Reference to a Pointer.
// http://www.learncpp.com/cpp-tutorial/74-passing-arguments-by-address/

#include <iostream>
using namespace std;

class A
{
public:
    void increment()
    {
        (*_x)++;
    }

    int getX()
    {
        return *_x;
    }

    // Get the address of the Variable that is passed in main.
    // x will now have &y2
    // x addr: 0x246ff08
    A (int* &x)
    {
        cout << "x : " << x << endl;
        // _x will now have &y2
        // So *_x can be used to get to the value of y2
        _x = x;
        cout << "_x : " << _x << endl;
    }

private:
    // _x will have &y2
    int* _x;
};

int main()
{
    cout << "Changing Class Private Variable" << endl;

    // y2 Addr: 0x246ff08
    // y1 Addr: 0x246ff04
    int y2 = 5;
    int *y1 = &y2;

    cout << "y1 Addr: " << &y1 << endl;
    cout << "y2 Addr: " << &y2 << endl;

    A *obj1 = new A(y1);
    // This gives a compile time error. warning: initialization of non-const reference int *&' from rvalue `int *'
    // A *obj1 = new A(&y2);
    obj1->increment();

    cout << "obj1.getX(): " << obj1->getX() << endl;
    cout << "y1: " << y1 << endl;
    cout << "y2: " << y2 << endl;

    cout << endl;
    return 0;
}
