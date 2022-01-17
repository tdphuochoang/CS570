/*
 * alphabetcountmulthreads.c - this file implements the alphabetcountmulthreads function.
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h> 
#include <stdlib.h>
#include <pthread.h>
#include "count.h"

/**
  The alphabetcountmulthreads function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite. Different with programming assignment#0, you need to implement the program using mutithreading.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z, which should be already up-to-date;
      num_threads - number of the threads running in parallel to process the files
      
       
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Requirements:
1)	Multiple threads are expected to run in parallel to share the workload, i.e. suppose 3 threads to process 30 files, then each thread should process 10 files;
2)	When a thread is created, a message should be print out showing which files this thread will process, for example:
Thread id = 274237184 starts processing files with index from 0 to 10!
3)	When a file is being processed, a message should be print out showing which thread (thread_id = xxx) is processing this file, for example:
Thread id = 265844480 is processing file input_11.txt
4)	When a thread is done with its workload, a message should be print out showing which files this thread has done with work, for example:
      Thread id = 274237184 is done !
5)	The array: long alphabetfreq[ ] should always be up-to-date, i.e. it always has the result of all the threads counted so far.  [You may need to use mutexes to protect this critical region.]


You should have the screen printing should be similar as follows:

 Thread id = 274237184 starts processing files with index from 0 to 10!
 Thread id = 265844480 starts processing files with index from 11 to 22!
 Thread id = 257451776 starts processing files with index from 23 to 31!

 Thread id = 265844480 is processing file input_11.txt
 Thread id = 257451776 is processing file input_22.txt
 Thread id = 274237184 is processing file input_00.txt
  � � 

 Thread id = 274237184 is done !
 Thread id = 265844480 is done !
 Thread id = 257451776 is done !

 The results are counted as follows:
 a -> 2973036
 b -> 556908
 c -> 765864
 �  � 
*/
#define MAX_FILENAME_LENGTH 200

struct acfArgs {
  int startIndex;
  int lastIndex;
  int numOfFiles;
  char **filePaths;
  long *alphabetFreq;
};
const char *getFileExt(const char *fileName) {
    // Finds the (first) location of the '.' character
    // and returns a pointer to the first character after that,
    // effectively returning a substring of the characters after the dot
    const char *dot = strrchr(fileName, '.');
    if (!dot || dot == fileName) {
        return "";
    }
    return dot + 1;
}

void *alphabetCountFiles(void *args) {
    struct acfArgs data = *((struct acfArgs*) args);

    
    printf("Thread id = %lu starts processing files with index from %d to %d!\n", pthread_self(), data.startIndex, data.lastIndex);
    
    
    FILE *file;
    for (int i = data.startIndex; i <= data.lastIndex; i ++) {
        printf("Thread id = %lu is processing file %s\n", pthread_self(), data.filePaths[i]);
        file = fopen(data.filePaths[i], "r");
        if (file) {
            // For each character, check if it's in range of uppercase or lowercase letters
            // and add to the count of the appropriate letter
            int c = fgetc(file);
            while (!feof(file)) {
                if ((c >= 65) && (c <= 90)) 
                    // Is Uppercase
                    c = c + 32;
                    
                if((c >= 97) && (c <= 122)) {
                    // Is Lowercase
                    data.alphabetFreq[c - 97] = (long) data.alphabetFreq[c - 97] + 1;
                }
                c = fgetc(file);
            }
            fclose(file);
            
            
        }
        
    }
    printf("Thread ID = %lu is done!\n", pthread_self());
    
}

char * new_string(char *str){
  char *ret;
  ret = (char *) malloc(sizeof(char) * 255);
  strcpy(ret, str);
  return(ret);
}

void alphabetcountmulthreads(char *path, char *filetowrite, long alphabetfreq[], int num_threads) {
    int numOfTextFiles = 0;
    struct dirent *dir;
    DIR *d = opendir(path);
    if (d == NULL) {
        printf("Could not open directory.\n");
        return;
    }
    int c;
    FILE *file;
    // Check each file in the directory, and if it has a txt extension, count it
    while ((dir = readdir(d)) != NULL) {
        if (strcmp(getFileExt(dir->d_name), "txt") == 0) {
            numOfTextFiles ++;
        }
    }
    
    rewinddir(d);
    int filesPerThreadBase = numOfTextFiles / num_threads;
    int threadsWithExtraFile = numOfTextFiles % num_threads;
    
    
    char *myList[numOfTextFiles]; //Array of file address strings. 
    int currentIndex = 0;
    // Check each file in the directory, and if it has a txt extension, add its full path to the list
    while ((dir = readdir(d)) != NULL) {
        if (strcmp(getFileExt(dir->d_name), "txt") == 0) {
            char p[MAX_FILENAME_LENGTH];
            strcpy(p, path);
            strcat(p, "/");
            strcat(p, dir->d_name);
            myList[currentIndex] = new_string(p);
            currentIndex ++;
        }
    }
    
    pthread_t threadPool[num_threads];
    int threadIDs[num_threads];
    struct acfArgs args[num_threads];
    currentIndex = 0;
    for (int i = 0; i < num_threads; i ++) {
        args[i].startIndex = currentIndex;
        args[i].lastIndex = currentIndex + filesPerThreadBase - 1;
        args[i].numOfFiles = numOfTextFiles;
        args[i].filePaths = myList;
        args[i].alphabetFreq = alphabetfreq;
        currentIndex += filesPerThreadBase;
        if (i < threadsWithExtraFile) {
            args[i].lastIndex ++;
            currentIndex ++;
        }
        threadIDs[i] = pthread_create(&threadPool[i], NULL, alphabetCountFiles, &args[i]);
    }
    for (int i = 0; i < num_threads; i ++) {
        pthread_join(threadPool[i], NULL);
    }
    FILE *g = fopen(filetowrite, "w"); //opens result.txt for writing
    fclose(g);
    
    
    
    closedir(d);
}


  

