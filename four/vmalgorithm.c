/*
 *  Implementation of FIFO and LRU page replacement algorithm
 *  Please add appropriate level of comments in this file 
 */

#include "vmalgorithm.h"
#include <stdlib.h>
#include <time.h>


/* Generate an access pattern
 * Example: 3, 2, 2, 1, 1  indicates the page 3, 2, 2, 1, 1 in order
 */
void generateAccessPattern()
{
   int i;
   srand(time(0));
   accessPattern = (int *)malloc( sizeof(int) * AccessPatternLength);   
   printf("The randomized Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
		     accessPattern[i] = rand() % ReferenceSZ;
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");
}

/*
 * Initialize the parameters of simulated memory
 */
void initializePageFrame()
{
   int i;
   memory.PageFrameList = (int *)malloc( sizeof(int)* FrameNR );    // dynamic allocated FrameNR frames to be used in memory
   memory.nextToReplaced =0;          // indicate the new frame to be replaced as 0
   for(i=0; i< FrameNR; i++)
   {
			memory.PageFrameList[i] = -1;  // initialization to -1 indicating all frames are unused 
   }

}

// Print the pages loaded in memory
void printPageFrame()
{
   int i;
   for(i=0; i< FrameNR; i++)
   {
			printf("%2d ",memory.PageFrameList[i]);       
   }
   printf("\n");
}


/*
 *  Print the access pattern in order
 */
void printAccessPattern()
{
   int i;
   printf("The Same Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");

}


/*
 * Return: number of the page fault using FIFO page replacement algorithm
 */
int FIFO()
{
   int i, j, n, k, flag, page_fault = 0;
   j = 0;
   for(i = 0; i < AccessPatternLength; i++){
      flag = 0; //Set available flag to 0
      for(k = 0; k < FrameNR; k++)
      //Compare input of page request to existing content of PageFrameList
      if(memory.PageFrameList[k] == accessPattern[i]){ 
         flag = 1; //Flag is 1 page is found
      }
      //Input page requested not existing in Frame
      if (flag == 0){  
         memory.PageFrameList[j] = accessPattern[i]; // place page requested at jth location in PageFrameList
         j = (j+1) % FrameNR; //Updating j for next round
         page_fault++;
      }
      printPageFrame();

   }  
   return page_fault;
   
}



/*
 * Return: number of the page fault using LRU page replacement algorithm
 */

int LRU()
{  
   int i, j, k,s, status[20], index, tmp;
   int page_fault = 0, flag = 0;
   for (i = 0; i< AccessPatternLength; i++){
      flag = 0;
      for(j = 0; j < FrameNR; j++){
         //Compare input of page request to existing content of PageFrameList
         if(memory.PageFrameList[j] == accessPattern[i]){
            flag =1; //Flag is 1 page is found
            break;
         }
      }
      //Input page requested not existing in Frame
      if(flag == 0){
         for(j = 0; j< FrameNR; j++)
            status[j] = 0;
            //Check on previous value of i 
         for(j = 0, tmp = i -1; j < FrameNR -1; j++, tmp--){
            for(k = 0; k< FrameNR; k++){
               if(memory.PageFrameList[k] == accessPattern[tmp]){
                  status[k] = 1;
               }
                  
            }
         }

         //Put the page where the status = 0
         for(j = 0; j < FrameNR ; j++){
            if(status[j] == 0){
               index = j;

            }
         }
         memory.PageFrameList[index] = accessPattern[i]; // place page requested at index location in PageFrameList
         page_fault++;
      }
      printPageFrame();
   }
   
   return page_fault;

}

