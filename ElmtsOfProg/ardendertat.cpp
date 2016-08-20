//	g++ compute_unique_blocks_hash_boost.cpp -I /PRAGADHEESH/Software/Boost/boost_1_50_0
// g++ -Wall ardendertat.cpp -I /home/pragadheesh/Software/Boost/boost_1_50_0

#include <iostream>
#include <cstdlib>
#include <set>
//#include <boost/unordered_set.hpp>
#include <iterator>
using namespace std;

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int *)b);
}

//Given an integer array, output all pairs that sum up to a specific value k.
void array_pair_sum_1(int a[], int n, int sum)
{
	for(int i = 0; i < n; i++)
	{
	// j = 1 repeats pairs; j = i does not repeats pairs; j = i+1 avoids duplicate pairs like 5+5 = 10
//		for(int j = 1; j < n; j++)
		for(int j = i+1; j < n; j++)
		{
				if((a[i] + a[j]) == sum)
				{
					cout<<a[i]<<","<<a[j]<<"; "<<endl;
				}
		}
	}
}

void array_pair_sum_2(int a[], int n, int sum)
{
	qsort(a,n,sizeof(int),compare);
	for(int i = 0, j = n-1; i < j;)
	{
		if(a[i] + a[j] > sum)
			j--;
		else if (a[i] + a[j] < sum)
			i++;
		else
		{
			cout<<a[i]<<","<<a[j]<<"; "<<endl;
			i++; j--;
		}
	}
}

void array_pair_sum_3(int a[], int n, int sum)
{
//	boost::unordered_set <int> arr_values;
//	boost::unordered_set <int>::iterator it;
	set<int> arr_set;
	set<int>::iterator it2;

	arr_set.insert(a[0]);
				
	for(int i = 1; i < n; i++)
	{
		if((it2=arr_set.find(sum-a[i])) != arr_set.end())
			cout<<a[i]<<","<<*it2<<endl;
		else
			arr_set.insert(a[i]);
	}
}

//Given an array of integers (positive and negative) find the largest continuous sum.
int largest_continuous_sum(int a[], int n)
{
	int osum = a[0], nsum = a[0];
	for(int i = 1; i < n; i++)
	{
		osum = max(osum+a[i], a[i]);
		nsum = max(osum,nsum);
	}
	return nsum;
}

int main()
{
	int a[] = {-3,-4,-8,2,-3,6,-7};
	array_pair_sum_3(a,7,8);
	cout<<"LCS: "<<largest_continuous_sum(a,7);
	cout<<endl;
	return 0;
}
