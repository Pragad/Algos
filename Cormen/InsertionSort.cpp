#include <iostream>

#ifdef _WIN32
typedef char 	                int8_t;
typedef unsigned char 	        uint8_t;
typedef unsigned short int 	    uint16_t;
typedef unsigned int 	        uint32_t;
typedef unsigned long long int 	uint64_t;
#else
#include <stdint.h>
#endif


void insertionSort(int a[], uint32_t n)
{
}

int main()
{
    int a[] = {4, 3, 2, 1};

    uint32_t numElmts = sizeof(a)/sizeof(a[0]);
    insertionSort(a, numElmts);

    cout << endl;
    return 0;
}
