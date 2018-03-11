import java.io.*;
import java.util.*;
// https://www.linkedin.com/in/jianminchen

/*
refdash.com 
two mock interview - cruiseautomation, uber, 
3.2

1. https://codereview.stackexchange.com/questions/182491/learn-trie-through-leetcode-212
2. http://www.cnblogs.com/grandyang/p/6006000.html
3. Given a list of float numbers, and four operators +, -, *, / with flat preference, find the maximum value 
by inserting operator between each consecutive pair of numbers.

For example, given the array [1, 12, -3], the maximum number 33 can be found using 1 - 12 * (-3), since all 
operators have flat preference, so 1 - 12 * (-3) will be handled from left to right, first operation is 1 - 12 
with value -11, and then second operation is -11 * (-3) = 33.

4.
Given an array of positive integers, return the number of triangles that can be formed 
with three different array elements as three sides of triangles. 
For example, if the input array is {4, 6, 3, 7}, the output should be 3. 
There are three triangles possible {3, 4, 6}, {4, 6, 7} and {3, 6, 7}. 
Note that {3, 4, 7} is not a possible triangle.

https://www.hackerrank.com/jianminchen_fl

5. https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

6.
Given a set of strings, e.g. {“one”, “cat”, “two”, “four”}, 
and a target string, e.g. “fouroneone”, return true if the target string is 
composed of elements from the set. 	
“onecat” -> true
“fouron” -> false
“twone” -> false
one, cat, two, four
a target string fouroneone
target string is composed of elementes from the set

https://gist.github.com/jianminchen/d597afdd55b000ed363e3898e29b194c

https://www.programcreek.com/2014/03/leetcode-word-break-ii-java/

7.
* Get the minimum required parentheses from the given parentheses. 
Note that it should also remove invalid parentheses.
* For example: ")(((())())((" -> "(()())"
* For example: "((()))" -> "()"


(()) -> () -> preserve the order 
(()()) -> (c)((a)(b))

refdash.com - cruise automation 

Lyft, airtable, pagerDuty, interana, zenysis, mixpanel, Uber, C3 IoT, Wonder workshop, Cruise Automation 




[2, 1, 3, 5, 4]  - N, 1 - N
[2, 1], [3], [5, 4] -> sorted array
what is maximum number of chunks?  
[2, 1, 4, 3, 6, 5]
[2, 1] [3, 4] [5, 6]

[2, 4, 3, 1]

[2, 4, 3, 1, 6, 5]
i: 0 (arr[i] - i)

i = i + abs(arr[i] - i); abs(arr[i] - i)
  
  3
         0  1  2  3  4  5  6
Case 1: [2, 4, 3, 7, 6, 5, 1] -> Return 1

         0  1  2  3  4  5  6
Case 2: [2, 4, 3, 1, 6, 7, 5] -> When I am at 1, i - arr[i] = -2, 

work on paper, write down/ go to interview - 5 minutes / 

-  
convert to binary tree to double link list

dynamic program - 90%

45 minutes - 

interviewing.io  

quora.com
100 keep mock interview -> tell -> 

24 problem -> 500 - without 10 minutes, 2 question, 20 minutes -> failed you
max/ min, max, major hint 2/ 4 
spiral matrix -> while, 4 for loop -> 10 minutes, let me pass, fail you

     3
   2   1 

extended algorithm can be solved in O(n) time complexity, array number can by any number. 

  
input: PAYPALISHIRING, numberOfRows = 4
  
P    I     N
A  L S   I G
Y A  H R
P    I 

output: PINALSIGYAHRPI

four of queue 
PIN <- 
ALSIG
YAHR
PI
-> id -> 0, 1, 2, 3, 2, 1, 0 1, 2, 3 -> O(N)


https://codereview.stackexchange.com/a/183006/123986


leetcode 
  1234
  
  let 1111 -> 1 number is correct , 1 number at correct position
      2111 -> 2q number is correct , 0 number at correct position
      4 digits, 4 position 
      10^4 * 4 * 3 * 2 * 1
      minimum questions I should ask 24 choices
      0 - 9 10 -> one digit - 4 distinct 
      taking 10, give digits 4 digit , 10 times - 9 times
      2 digits
      3 digits
      4 digits
      identify -> 
      
      10 times -> at time 
      four digits - at most -> 0, 1, 2, ,
      1, 2, -> add new digit <- 
*/

class Solution {
  
  /*
  match every open bracket has a corresponding close
  bracket
  
  return: number of brackets not matching
  No other bracket types like {}, []
  
  0 1 2 3 4 5 6 7 8
  ( ( ) ) ) ) ( ( ) 
  
  countUnmatchedBracket = 0
  i:0, cnt = 1
  i:1, cnt = 2
  i:2, cnt = 1
  i:3, cnt = 0
  i:4, countUnmatchedBracket = 1
  i:5, countUnmatchedBracket = 2
  i:6, cnt = 1
  i:7, cnt = 2
  i:8, cnt = 1
  return countUnmatchedBracket + cnt;
  */
  static int bracketMatch(String text) {
    if (text == null) {
      return 0;
    }       
    
    int countUnmatchedBracket = 0;
    int countOpenBracket = 0;
    
    for (char c : text.toCharArray()) 
    {
      if (c == '(') 
      {
        countOpenBracket++;
      } 
      else 
      {
        if (countOpenBracket == 0) 
        {
          countUnmatchedBracket++;
        } 
        else 
        {
          countOpenBracket--;
        }
      }
    }
    
    return countOpenBracket + countUnmatchedBracket;
  }

  public static void main(String[] args) {
  }
}
