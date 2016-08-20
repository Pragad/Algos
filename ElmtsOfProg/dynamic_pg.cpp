#include<iostream>
#include<string>
#include<cstring>
#include<climits>
using namespace std;

//1. Longest Common Subsequence - Recursion top down
//2. Longest Common Subsequence - Recursion bottom up
//3. Longest Common Subsequence - DP Recursion
//4. Longest Common Subsequence - DP without recursion

//5. Longest Palindrom string - DP without recursion
//6. Longest Common sub-string - DP without recursion

//7. Longest increasing sub sequence 1 - NO Recursion
//8. Longest increasing sub sequence 2 - Recursion
//9. Edit distance between two strings

//10. Longest non-repeating substring
//11. Minimum jumps to reach end of array
//12. Minimum jumps to reach end of array - Dynamic Programming
//13. Coin change problem

int lcss(string a, string b)
{
	if(a.length() == 0 || b.length() == 0)
		return 0;
	if(a[0] == b[0])
		return 1+lcss(a.substr(1), b.substr(1));
	else
		return max(lcss(a.substr(1), b), lcss(a, b.substr(1)));
}

int lcss_2(string a, string b)
{
	if(a.length() == 0 || b.length() == 0)
		return 0;
	if(a[a.length()-1] == b[b.length()-1])
		return 1+lcss(a.substr(0,a.length()-1), b.substr(0,b.length()-1));
	else
		return max(lcss(a.substr(0,a.length()-1), b), lcss(a, b.substr(0,b.length()-1)));
}

int lcss_dp_rec(string a, string b)
{
	int subseq[a.length()+1][b.length()+1];
	if(a.length() == 0 || b.length() == 0)
		return 0;
	if(a[a.length()-1] == b[b.length()-1])
		return 1+lcss(a.substr(0,a.length()-1), b.substr(0,b.length()-1));
	else
		return max(lcss(a.substr(0,a.length()-1), b), lcss(a, b.substr(0,b.length()-1)));
}

int lcss_dp(string a, string b)
{
	int subseq[a.length()+1][b.length()+1];
	for(int i = 0; i <= a.length(); i++)
	{
		for(int j = 0; j <= b.length(); j++)
		{
			if(i == 0 || j == 0)
				subseq[i][j] = 0;
			else if (a[i] == b[j])	
				subseq[i][j] = 1 + subseq[i-1][j-1];
			else
				subseq[i][j] = max(subseq[i][j-1], subseq[i-1][j]);
		}
	}
	return subseq[a.length()][b.length()];
}

//http://www.geeksforgeeks.org/archives/25463
int long_palin_str(string a)
{
	bool table[a.length()][a.length()];
	memset(table, 0, sizeof(table));

	int maxLength = 0;	
	for(int i = 0; i < a.length(); i++)
	{
		table[i][i] = true;
	}
	maxLength = 1;
	
	//Denotes starting position of the palindrome string
	int start = 0;

	for(int i = 0; i < a.length()-1; i++)
	{
		if(a[i] == a[i+1])
		{	
			table[i][i+1] = true;
			maxLength = 2;
			start = i;
		}
	}
	
	for(int k = 3; k <= a.length(); k++)
	{
		for(int i = 0; i < a.length()-k+1; i++)
		{
			int j = i+k-1;
			if(table[i+1][j-1]  && a[i] == a[j])
			{
				table[i][j] = true;
				if(maxLength < k)
				{
					maxLength = k;
					start = i;
				}
			}
		}
	}
	
	for(int i = start; i < maxLength+start; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	return maxLength;
}

char* longest_common_substring(string a, string b)
{
//	int matrix[a.length()+1][b.length()+1] = {0};
	int x = a.length()+1;
	int y = b.length()+1;
	int matrix[x][y];
	memset(matrix, 0, x*y*sizeof(int));
	int max = 0, maxi = 0, maxj = 0;
	for(int i = 0; i < a.length(); i++)
	{
		for(int j = 0; j < b.length(); j++)
		{
			if(a[i] == b[j])
			{
				if(i == 0 || j == 0)
				{
					matrix[i][j] = 1;
				}
				else
				{	
					matrix[i][j] = matrix[i-1][j-1]+1;
				}
				if(max < matrix[i][j])
				{
					max = matrix[i][j];
					maxi = i; maxj = j;
				}
			}					
		}
	}
	
	cout<<"Max: "<<max<<endl;
	cout<<"Max i: "<<maxi<<endl;
	cout<<"Max j: "<<maxj<<endl;	
	char* c = new char[max];
	for(int i = 0; i < max; i++)
	{
		c[i] = a[maxi-max+i+1];
	}
	c[max] = '\0';
	return c;
}

//Dynamic Programming
int longest_increasing_subseq(int a[], int n)
{
//	if(n==1)
	int* list = new int[n];
	for(int i = 0; i < n; i++)
	{
		list[i] = 1;
	}
	
	
	for(int i = 1; i < n; i++)
	{
		for(int j = 0; j < i; j++)
		{
			if(a[i] > a[j] && list[i]<list[j]+1)
			{
				list[i] = list[j]+1;
			}
		}
	}
	
	int max = list[0];
	for(int i = 1; i < n; i++)
	{
		if(list[i] > max)
			max = list[i];
	}
	return max;
}

int longest_increasing_subseq_2(int a[], int a_sort[], int s, int e, int s2)
{
	if(s < e && s2 < e)
	{
		if(a[s] == a_sort[s2])
			return 1+longest_increasing_subseq_2(a, a_sort, s+1, e, s2+1);
		else 
			return max(longest_increasing_subseq_2(a, a_sort, s+1, e, s2), longest_increasing_subseq_2(a, a_sort, s, e, s2+1));
	}
	return 0;
}

int edit_distance(string a, string b)
{
	if(a.length() == 0 && b.length()==0)
		return 0;
	else if(a.length() == 0)
		return b.length();
	else if(b.length() == 0)
		return a.length();
	
	int x = edit_distance(a.substr(0,a.length()-1), b) + 1;
	int y = edit_distance(a, b.substr(0,b.length()-1)) + 1;
	int z = edit_distance(a.substr(0,a.length()-1), b.substr(0,b.length()-1)) + (a[a.length()-1] != b[b.length()-1]);	

	return min(min(x,y),z);
}

int longest_non_repeating_substr(string a)
{
	int* visited = new int[256];
	memset(visited, -1, sizeof(int)*256);
	
	int cur = 0, max = 0;
	int prev_index;
	visited[a[0]] = 0;
	for(int i = 0; i < a.length(); i++)
	{
		prev_index == visited[a[i]];
		
		if(prev_index == -1 || i - cur > prev_index)
		{
			cur++;
		}	
		
		else
		{
			if(cur > max)
			{
				max = cur;
			}
			cur = i - prev_index;
		}
		visited[a[i]] = i;	
	}
}

//http://www.geeksforgeeks.org/archives/13209
int minJumps(int a[], int l, int h)
{
	if(l==h)
		return 0;
	if(a[l] == 0)
		return -1;
	if(a[l]+l>=h)
		return 1;
	return 1+min(minJumps(a,l+1,h), minJumps(a,a[l]+l,h));	
}

int minJumps_dp(int a[], int l, int h)
{
	int jump[h];
	
	for(int i = 0; i < h; i++)
		jump[i] = INT_MAX;
	
	if(l==h)
		return 0;
	if(a[l] == 0)
		return -1;
	if(a[l]+l>=h)
		return 1;
	
	jump[0] = 0;
	if(a[0] != 0)
		jump[1] = 1;
	else
	{
		jump[1] = 0;
		return -1;
	}
	
	for(int i = 0; i < h; i++)
	{
		for(int j = i+1; j <= i+a[i]; j++) 	
		{
			if(j < h)
			{
				if(jump[j] >= i+1)
					jump[j] = jump[i]+1; 
			}
			else
			{
				i = h;
				break;
			}	
		}
	}
	
	for(int i = 0; i < h; i++)
		cout<<jump[i]<<" ";
	cout<<endl;
	return jump[h-1];	
}

int coin_change(int coins[], int n, int sum)
{
	if(sum == 0)
		return 1;
	else if(sum < 0 || n <= 0)
		return 0;
	return coin_change(coins, n-1, sum) + coin_change(coins, n, sum-coins[n-1]);
}
int main()
{
	cout<<"LCS: "<<lcss_dp("ABCDGH","AEDFHR")<<endl;
	cout<<"LCS: "<<lcss_dp("GXTXAYB","AGGTAB")<<endl;	
	cout<<"Longest Common Substring: "<<longest_common_substring("fihello","hellowor")<<endl;
	
	int lis1[]  = {80,60,10,22,9,21,33,41,50};
	int lis2[]  = {9,10,21,22,33,41,50,60,80};
	cout<<"Longest Inc Subseq 1: "<<longest_increasing_subseq(lis1, sizeof(lis1)/sizeof(int))<<endl;
	cout<<"Longest Inc Subseq 2: "<<longest_increasing_subseq_2(lis1, lis2, 0, sizeof(lis1)/sizeof(int), 0)<<endl;
	
	cout<<"Edit Distance: "<<edit_distance("daySatur", "Saturday")<<endl;
	cout<<"Longest Palindrome Substring: "<<long_palin_str("llomadamhe")<<endl;
	
	int arr[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
	cout<<"Minimum Jumps 1: "<<minJumps(arr,0,11)<<endl;
	cout<<"Minimum Jumps 2: "<<minJumps_dp(arr,0,11)<<endl;
	
	int coins[] = {1,2,3};
	cout<<"Coin Change: "<<coin_change(coins,3,5)<<endl;
	cout<<endl;
	return 0;
}
