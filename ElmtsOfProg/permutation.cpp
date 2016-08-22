#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <cstring>
using namespace std;

void print_all_permutations(const string& s)
{
    string s1 = s;
    sort(s1.begin(), s1.end()); 
    do {
        cout << s1 << endl;
    } while (next_permutation(s1.begin(), s1.end()));
}

void swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void permute_swap(char* a,int i , int n)
{
	char duplicates[256];
	bzero(duplicates,256);
	if(i == n)
	{
		cout<<a<<endl;
	}
	else
	{
		int j = i;
		for(j = i; j < n; j++)
		{
			if(!duplicates[*(a+j)])
			{
				swap(a+i,a+j);
				permute_swap(a, i+1, n);
				swap(a+i, a+j);
				duplicates[*(a+j)] = 1;
			}
		}
	}
}

int main()
{
//    print_all_permutations("AAB");
//	 cout<<endl;
 	 char word[] = "AAB";
	 permute_swap(word, 0, strlen(word));
    return 0;
}

