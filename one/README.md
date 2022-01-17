# Programming assignment 1

## Hoang Tran
## RED ID: 821328424

The purpose of this project is familiarize the use of system  calls  such  as  fork,  exec,  wait,  exit  and  etc.,  to spawn and terminate other user programs.

**TODO:** Modify the files under the folder 'one'.

Here is the explaination of the modified code:

mulproc.c

* First intialize variables.
* Call fork() to create a new child process.
* State first condition: if pid1 < 0 then the creation of that child process is unsuccessful.
* State second condition: if pid1 == 0, a new child process is created. 
* Print a message to the output screen showing which child process (with PID) is running testspecial program. 
* Initialize the command and use execv() which executes the path of the executable file, in this case, testspecial. 
* State third condition, if pid1 > 0, create a new child process called pid2. 
* State first condition, if pid2 == 0, a new child process is created. 
* Print a message to the output screen showing which child process (with PID) is running testalphabet program.
* Initialize the command and use execv() which executes the path of the executable file, in this case, testalphabet. 
* Use waitpid() to wait for a child to exit. If pid1 is terminated, wait for pid1 to exit then print out a message. If pid2 is terminated, wait for pid2 to exit then print out a message. 
 

### Test result:
make 
./mulproc 

CHILD <PID: 271> process is executing testspecial program!
CHILD <PID: 272> process is executing testalphabet program!
, -> 745668
. -> 798072
: -> 15708
; -> 32340
! -> 63228
CHILD <PID: 270> process has done with testspecial program! See the results above!
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
CHILD <PID: 270> process has done with testalphabet program! See the results above!




 