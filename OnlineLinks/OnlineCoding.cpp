#include <iostream>
#include <vector>

using namespace std;

// This function checks if each character falls within 'a' to 'z'
bool validate(const string & s)
{
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] < 'a' || s[i] > 'z')
        {
            return false;
        }
    }
    
    return true;
}

// This function sorts the given string
void sort(string * s)
{
    for(int i = 1; i < s->length(); i++)
    {
        int j = i;
        char a = (*s)[j-1];
        char b = (*s)[j];
        
        while(j > 0 && (*s)[j-1] > (*s)[j])
        {
            char tmp = (*s)[j - 1];
            (*s)[j - 1] = (*s)[j];
            (*s)[j] = tmp;
            j--;
        }
    }
}

// This function removes the duplicate characters from the string.
void uniq(string * s)
{
    char t[26] = {0};
    
    for(int i = 0; i < s->length(); i++)
    {
        char c = (*s)[i];
        t[(c - 'a')] = 1;
    }
    
    *s = "";
    
    for(int i = 0; i < 26; i++)
    {
        if(t[i] != 0)
        {
            *s += (i +  'a');
        }
    }
}

void genperms(
    vector<string> & permutations, 
    const string & p, 
    int nextIndex, 
    const string & s, 
    const string & alphabet)
{
    // Should have a nicer basecase
    if (nextIndex >= s.length())
    {
        return;    
    }   
    
    // The below "next" is not being used anywhere
    // char next = s[nextIndex];
    
    for(int i = 0; i < alphabet.length(); i++)
    {
        char c = alphabet[i];
        
        string px = p + c;
        
        if(px.length() < s.length())
        {
            genperms(permutations, px, nextIndex + 1, s, alphabet);
        }
        else
        {
            // We are pushing to 'permutations' only when px is less than s.
            if(px < s)
            {
                permutations.push_back(px);
            }
            else
            {
                // Optimization: We can safely break once we reach "px" that is same as "s"
                break;    
            }
        }
    }
}

int main()
{
  string s;
  
  getline(cin, s);
    
  if(validate(s) != true)
  {
    cout << s << endl;
    cout << "-1" << endl;
    return 0;
  }
   
  string alphabet = s;
  vector<string> permutations;
  
  // Print outputs and make sure that "Sort" and "Uniq" works correctly  
  cout << "1. Alpha: " << alphabet << endl;
  sort(&alphabet);
  cout << "2. Alpha: " << alphabet << endl;
  uniq(&alphabet);
  cout << "3. Alpha: " << alphabet << endl;
  
  // This will generate all permutations that is lesser than giving string.
  // So for "abc" we get only till "abb"
  // However for "cba" we get till "cac"
  genperms(permutations, "", 0, s, alphabet);
  
  cout << "Original String: " << s << endl;
    
  //Print elements in permutations
  for (auto str : permutations)
  {
    cout << str << ", ";    
  }
  cout << endl;
    
  cout << "Permutations Length: " << permutations.size() << endl;
  
  return 0;
}
