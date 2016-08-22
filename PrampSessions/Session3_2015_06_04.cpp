/*
 * Q: Count the number of islands in a matrix
 *
 * LEARNINGS:
 *      Interviewee:
 *      1. Be prepared to handle situations when INPUT is HUGE and can't
 *         fit in memory
 *      2. Be familar with Iterative apporach and Coverting a Recursive code
 *         to Iterative Version
 *      3. Space Complexity of Recursive code can't be Constant
 *      4. First write Pseudo Code and try with few inputs and do a DRY RUN
 *      5. Then cleanup the code and handle EDGE CASES
 *      6. Make your code READABLE, RESUSABLE and MAINTAINABLE
 *
 *      Interviewer:
 *      1. Don't give away the answers or find mistakes till they are done.
 *         Give slight hints; Don't be very explicit.
 *         Eg: Pointing out Array Size and End Index
 */

int ROWPOS = {-1, -1, -1, 0, 0, 1, 1, 1};
int COLPOS = {-1, 0, 1, -1, 1, -1, 0 1};
// Say i = 2, j =2
//1,1; 1,2; 1,3;...
// Space Complexity: O();

void dfs(int** twoDMatrix, int i, int j, int rows, int cols)
{
   twoDMatrix[i][j] = 2;
   for (int k = 0; k < 8; k++)
   {
      int nextI = i + ROWPOS[k];
      int nextJ = j + COLPOS[k];
     
      if (nextI >= 0 && nextI < rows && nextJ >=0 && nextJ < cols &&
          twoDMatrix[nextI][nextJ] == 1)
      {
         dfs(twoDMatrix, nextI, nextJ, rows, cols);
      }
   }
}

int countIslands(int** twoDMatrix, int rows, int cols)
{
   int numIslands = 0;
   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < cols; j++)
      {
         if (twoDMatrix[i][j] == 1)
         {
            dfs(twoDMatrix, i, j, rows, cols);
            numIslands++;
         }
      }
   }
  
   return numIslands;
}

int searchIndexEqElem(int * A, int size, int key){
   int start = 0;
   int end = size-1;
   int mid;
   while(start <=end){
      mid = (end-start)/2 +start;
      if (A[mid] < mid)
         start = mid+1;
      if (A[mid] > mid)
         end = mid-1;
      else
       return mid;
   }
   return -1;
}
