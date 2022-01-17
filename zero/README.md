# Programming assignment 0

## Hoang Tran
## RED ID: 821328424

The purpose of this project is to count the frequency of each alphabet letter (a-z, total 26 case insensitive) and five specialcharacters (‘.’, ‘,’, ‘:’, ‘;’ and ‘!’) in all the .txt files under a given directory. 

**TODO:** Modify the files under the folder 'zero.

Here is the explaination of the modified code:

alphabetcount.c

* First intialize variables and pointers.
* Open the current directory by using opendir() which returns a pointer of DIR type
* If the directory is readable, assign the current file name to the string 'filename' for testing. 
* Check for .txt extension file. Increment isTxt if the filename contains letter 't' or 'x'
* isTxt should be 3 when a .txt file is read. Store validated files into list. 
* strcpy(p, path) to concatenates the full data directory to p and then use strcat to append the string. 
* Use fopen() to open the file path for reading. 
* Use fgetc() to get the first character in the file. 
* The ascii code for A-Z is from 65 to 90. While not end of file, convert the upper case character to lower case by adding 32 to the proper ascii code.  
* If the lower case characer is found, increments desired character counter. c-97 corresponds to each lowercase's location in the alphabetfreq[].
* Re-initializes fgetc for next character in while loop. 
* USe fclose() to close the file when done. 
* Use fopen() to open result.txt for writing.
* Use closedir() to close the directory. 

specialcharcount.c 

* The method is the same as alphabetcount.c except for the implementation to recognize special charaters and increment the counter of that character located in the array charfreq[].

### Test results:

result.txt 

a -> 2973036
b -> 556908
c -> 765864
d -> 1786752
e -> 4883076
f -> 765336
g -> 809292
h -> 2818068
i -> 2586276
j -> 35112
k -> 401412
l -> 1728276
m -> 1050852
n -> 2509320
o -> 2766192
p -> 562848
q -> 28776
r -> 2177076
s -> 2465496
t -> 3291684
u -> 1015608
v -> 276804
w -> 1085040
x -> 46860
y -> 730752
z -> 12936


specialresult.txt 

, -> 745668
. -> 798072
: -> 15708
; -> 32340
! -> 63228




 