// Imp: Think of Naive Solution and tell that first
// Make sure you don't get compilation error. In for loop if using "i" after loop declare it before the for loop

// Logic:
// Step 1: Reverse the entire character set
// Step 2: Traverse
// hello
void reverseWord(char* str, int32_t startIdx, int32_t endIdx)
{
   if (startIdx <= endIdx)
   {
      return;
   }
  
   for (int32_t i = startIdx, j = endIdx; i < j; i++, j--)
   {
      char temp = str[i];
      str[i] = str[j];
      str[j] = temp;
   }
}
// my name is xyz
// zyx si eman ym

// ip: "__ my name is ___"
// reversed string: "___ si eman ym __"
// op: "___ is name my __"

void reverseSentence(char* str, uint32_t strLen)
{
   if (strLen == 0 || strLen == 1)
   {
      return;
   }
  
   // Reverse the complete string
   reverseWord(str, 0, strLen - 1);
  
   // Find space and reverse that part of the string
   int32_t i = 0;
   int32_t stIdx = 0;
   for (; i < strLen; i++)
   {
      if (str[i] == ' ')
      {
         reverseWord(str, stIdx, i-1);
      //   str[i] = ' ';
         stIdx = i + 1;
      }
   }
  
   if (stIdx < i)
   {
      reverseWord(str, stIdx, i - 1);
   }
}
