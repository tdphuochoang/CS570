# Programming assignment 2

## Hoang Tran
## RED ID: 821328424

The purpose of this project is to count the frequency of each alphabet letter (a-z, total 26 case insensitive) in all the .txt files under a given directory using multithreading. POSIX Pthreads and mutexes can be used to create multithreading application. 

**TODO:** Modify the files under the folder 'two'.

Here is the explaination of the modified code:

alphabetcountmulthreads.c

Note: The technique to count the frequency of each alphabet letter in this program is pretty much the same as the implementation in program #0. The huge difference between them is program #2 receives command to create a number of threads. Each thread will run in parallel to process a certain amount of files. Thus, the progress to handle files will be speeded up.  

* In function alphabetcountmulthreads, first intialize variables and pointers.
* Open the current directory by using opendir() which returns a pointer of DIR type
* Check each file in the directory, and if it has a txt extension, count it
* Use rewinddir() reset the position of a directory stream to the beginning of a directory
* Calculate files per thread base and threads with extra files. 
* Create array of file address strings
* Check each file in the directory, and if it has a txt extension, add its full path to the myList array. 
* Create num_threads threads, each with its own assigned indexes.
* Threads will process the files within its range using same array and different indexes
* Initiate structure variables on top of the program. Use for loop to get each value for each structure variables as the 'i' increases. Use pthread_create to start a new thread in the calling process. 
* In calling function alphabetCountFiles, each thread will process a certain amount of files, from startIndex to lastIndex. The method co count the each alphabet letter is similar to program #0. Messages will be printed out during a file processing, and after the process finishes. 
*Use pthread_join() to wait for each thread to terminate. 
* Use fopen() to open result.txt for writing.
* Use closedir() to close the directory. 

### Test results:

result.txt 

make
./testmulthreads 3

Please enter 2 arguments only eg."./testmulthreads #_of__threads!!"
Thread id = 34360276896 starts processing files with index from 0 to 10!
Thread id = 34360276896 is processing file ../data/input_00.txt
Thread id = 34360277152 starts processing files with index from 11 to 20!
Thread id = 34360342960 starts processing files with index from 21 to 30!
Thread id = 34360277152 is processing file ../data/input_11.txt
Thread id = 34360342960 is processing file ../data/input_21.txt
Thread id = 34360276896 is processing file ../data/input_01.txt
Thread id = 34360342960 is processing file ../data/input_22.txt
Thread id = 34360277152 is processing file ../data/input_12.txt
Thread id = 34360342960 is processing file ../data/input_23.txt
Thread id = 34360277152 is processing file ../data/input_13.txt
Thread id = 34360276896 is processing file ../data/input_02.txt
Thread id = 34360277152 is processing file ../data/input_14.txt
Thread id = 34360342960 is processing file ../data/input_24.txt
Thread id = 34360276896 is processing file ../data/input_03.txt
Thread id = 34360277152 is processing file ../data/input_15.txt
Thread id = 34360342960 is processing file ../data/input_25.txt
Thread id = 34360276896 is processing file ../data/input_04.txt
Thread id = 34360342960 is processing file ../data/input_26.txt
Thread id = 34360277152 is processing file ../data/input_16.txt
Thread id = 34360276896 is processing file ../data/input_05.txt
Thread id = 34360342960 is processing file ../data/input_27.txt
Thread id = 34360277152 is processing file ../data/input_17.txt
Thread id = 34360276896 is processing file ../data/input_06.txt
Thread id = 34360276896 is processing file ../data/input_07.txt
Thread id = 34360277152 is processing file ../data/input_18.txt
Thread id = 34360342960 is processing file ../data/input_28.txt
Thread id = 34360276896 is processing file ../data/input_08.txt
Thread id = 34360277152 is processing file ../data/input_19.txt
Thread id = 34360342960 is processing file ../data/input_29.txt
Thread id = 34360276896 is processing file ../data/input_09.txt
Thread id = 34360277152 is processing file ../data/input_20.txt
Thread id = 34360342960 is processing file ../data/input_30.txt
Thread id = 34360276896 is processing file ../data/input_10.txt
Thread ID = 34360277152 is done!
Thread ID = 34360342960 is done!
Thread ID = 34360276896 is done!
The results are counted as follows : 
a -> 2917865
b -> 554999
c -> 762235
d -> 1769124
e -> 4745036
f -> 761661
g -> 805371
h -> 2770639
i -> 2544531
j -> 35105
k -> 400469
l -> 1709789
m -> 1043542
n -> 2471445
o -> 2718103
p -> 560691
q -> 28773
r -> 2148432
s -> 2425529
t -> 3220542
u -> 1010312
v -> 276379
w -> 1078326
x -> 46852
y -> 727840
z -> 12935




 