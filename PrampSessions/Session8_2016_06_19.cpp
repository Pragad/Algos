int main() {
   cout << "Practice Makes Perfect";
   return 0;
}

vector<int> ArrayProducts (vector<int> nums)
{
   int prod = 1;
   vector<int> ProdVec;
   vector<int> ResultVec;
   for (int32_t i = nums.size()-1; i >= 0; i--)
   {
      prod *= nums[i];
      ProdVec.insert(0, prod);
   }
  
   prod = 1;
   for (int32_t i = 0; i < nums.size(); i++)
   {
      if (i+1 < nums.size())
      {
         ResultVec.push_back(prod * ProdVec[i+1]);
      }
      else // For the last element
      {
         ResultVec.push_back(prod);
      }
      prod *= num[i] ;
   }
  
   return ResultVec;
}

// Space: O(N)
// time: O(N)
vector<int> ArrayProducts (vector<int> nums)
{  
   int prod = 1;
   vector<int> ProdVec;
   vector<int> ResultVec;
   for (int32_t i = nums.size()-1; i >= 0; i--)
   {
      prod *= nums[i];
      ProdVec.insert(0, prod);
   }
  
   prod = 1;
   for (int32_t i = 0; i < nums.size() - 1; i++)    // Array 0 to 4
   {

      ResultVec.push_back(prod * ProdVec[i+1]);     // prod: 0..2 * nums[4]
      prod *= num[i] ;                              // prod: 0..3
   }
   ResultVec.push_back(prod);                      
  
   return ResultVec;
}

