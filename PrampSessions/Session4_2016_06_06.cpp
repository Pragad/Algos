int getDesiredIndex(vector<int> arr, int low , int high)
{
   /*if(low>high)
      return -1;
  
   int mid = low + (high - low)/2;
  
   if(a[mid]== mid)
      return mid;
  
   if(a[mid]<mid)
      return getDesiredIndex(arr,mid+1,high);
   else
      return getDesiredIndex(arr,low ,mid-1);     
    */
  
   while(low<=high)
   {
      int mid = low + (high - low)/2;
  
      if(a[mid]== mid)
         return mid;
     
      if(a[mid]<mid)
        low = mid+1;
      else
         high =mid-1;     
     
   }
  
   return -1;
  
}
