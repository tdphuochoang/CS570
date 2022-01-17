/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h> 
#include "count.h"
#include <stdlib.h>

/**
  The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:
      alphabetfreq[0]: the frequency of 'a'
      alphabetfreq[1]: the frequency of 'b'
         ... ...
      alphabetfreq[25]:the frequency of 'z'

  
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     letter -> frequency
     
     example:
     a -> 200
     b -> 101
     ... ...
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/
void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
{
    
    DIR *d;
    char *filename;
    char *list;
    struct dirent *dir; 
    d = opendir(path); //open directory
    if(d != NULL) {
        while((dir = readdir(d)) != NULL) {
            filename = dir->d_name; //assigns current name to string filename
            size_t t = strlen(filename) - 3; //checks for .txt extentsion
            int isTxt = 0;
            while(t < strlen(filename)) {
                if(!(filename[t] == 't' || filename[t] == 'x'))
                    continue;
                else {
                    isTxt++; //add up the current letter 
                }
                t++;
            }
            if(isTxt == 3) { //files chosen only if "txt" is read
                list = dir->d_name; //stores validated file to be read
                char p[256];
                strcpy(p, path); //concatenates the full data directory to p
                strcat(p, "/");
                strcat(p, list);
                FILE *f = fopen(p, "r"); //opens the file path for reading
                if(f == NULL) { //can't open file, abort
                    return;
                }
                int c = fgetc(f); //get the first character in the file
                while(!feof(f)) {
                    if((c >= 65) && (c <= 90)) //convert upper case character to lower case
                        c = c + 32;
                    if((c >= 97) && (c <= 122)) { //if alphabet letter is found
                        alphabetfreq[c - 97] = (long) alphabetfreq[c - 97] + 1; //increments desired character counter. c-97 corresponds to each lowercase's location in the array
                    }
                    c = fgetc(f); //re-initializes fgetc for next character in while loop
                }
  
                fclose(f);
                FILE *g = fopen(filetowrite, "w"); //opens result.txt for writing
                
                fclose(g);
            }
        }
    }
    closedir(d); //close directory	
}
