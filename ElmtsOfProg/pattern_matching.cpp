#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void match_pattern(char text[], char pattern[])
{
	cout<<strlen(text)<<endl;
	cout<<strlen(pattern)<<endl;
	int count = 0;
	
	for(int n = 0; n < strlen(text);)
	{
		for(int i = 0; i < strlen(pattern); i++)
		{
			if(text[n] == pattern[i])
			{
				count++;
				n++;
			}
			else
			{
				if(count == strlen(pattern))
				{	
					cout<<"Pattern found at: "<<n-count<<endl;
				}
				count = 0;
				n++;
				break;
			}
		}
	}
}

int main()
{
	char text[] = "This is sample text strisng i";
	char pattern[] = "is";
	match_pattern(text, pattern);
	cout<<endl;
	return 0;
}
