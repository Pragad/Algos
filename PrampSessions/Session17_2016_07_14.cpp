// Learning: Always Pass by Const and Pass by Reference if bigger stuff
//
/*
for (int i = 0; i < tok.length(); ++i) {
            tok[i] = tolower(tok[i]);
            if (ispunct(tok[i])) {
                tok.erase(i--,1);
            }
        }
*/

// Complexity: // ++uniqWords[word];
// Pass by const reference
#include <iostream>
using namespace std;

int main() {
   cout << "Practice Makes Perfect";
   return 0;
}

// Time Complexity: Putting all elements to hash table: O(n)
//                  Read from hash table and build a heap: O(m log m) where m is the # unique words
// Space Complexity: O(m) where m is the number of unique elements in the list

struct Word
{
   string word;
   unsigned int count;
  
  
   bool operator >(const Word wrd)
   {
      return count > wrd.count;
   }
};

vector<string> uniqueWords(vector<string> words) // const vector<string> & words
{
   unordered_map<string, unsigned int> uniqWords;
  
   // Complexity: O(n) where n is the number of words
   for (auto word : words)
   {
      // ++uniqWords[word];
      auto itr = uniqWords.find(word);
      if (itr != uniqWords.end())
      {
         // Already present. Increment the count
         itr->second++;
      }
      else
      {
         uniqWords[word] = 1;
      }
   }
  
   // Complexity: m log(m) where m is the number of unique words
   priority_queue<Word> uniqWordsHeap;
   for (auto i = uniqWords.begin(); i != uniqWords.end(); i++)
   {
      uniqWordsHeap.push(Word(i->getKey(), i->getValue())); // Complexity: O(log m)
   }
  
   // Complexity: m log(m) where m is the number of unique words
   vector<string> result;
   while(!uniqWordsHeap.empty())
   {
      results.push_back(uniqWord.top().word + ": " + to_string(uniqWord.count)); // O(1)
      uniqWordsHeap.pop(); // O(log n)
   }
  
   return result;
}

// Time Complexity: O(n)
vector<string> findUniqueWords(string str)
{
   vector<string> result;
   vector<string> words;
  
   stringStream ss(str);
   string temp;
   /*
   while (getline(str, temp, ' '))
   {
      words.push_back(temp);
   }
   */
  
   unsigned int stIdx = 0;
   for (unsigned int i = 0; i < str.length(); i++)
   {
      /*
        for (int i = 0; i < tok.length(); ++i) {
            tok[i] = tolower(tok[i]);
            if (ispunct(tok[i])) {
                tok.erase(i--,1);
            }
        }
      */
     
      if (str[i] == ' ' || str[i] == '.' || str[i] == '!')
      {
         if (stIdx < i)
         {
            words.push_Back(str.substr(stIdx, (i - stIdx)));
            stIdx = i + 1;
         }
        
         // Move start index if we are at a punctuation
         if (stIdx == i)
         {
            stIdx++;
         }
      }
   }
  
   result = uniqueWords(words);
  
   return result;
}
//      0123456789
// ip: "my  ! name is he!llo.wor!ld"
// i:0, stIdx:0
// i: 2, stIdx: 0 Inside Loop
// stIdx < i; push(0, 2 - 0)
// stIdx 3

// i:3, stIdx: 3
// stIdx: 4;

// i:4, stIdx:4
// stdIdx: 5;


// words: my name is he llo wor ld



