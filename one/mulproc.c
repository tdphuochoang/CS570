#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> 
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 This program will fork two child processes running the two programs generated in programming zero in parallel.
 Hint: You mant need to use fork(), exec() family, wait(), exit(), getpid() and etc ...
 
 Requirements:
 
 1) Exactly two child processes are created, one to run testspecial program and the other is to run testalphabet program;
 2) When a program starts to run, print a message to the output screen showing which process (with PID) is running which program, for example:
    "CHILD <16741> process is executing testalphabet program!"
    
 3) When a program is done, the process exits and at the same time, a message should be print to the output screen showing which  process (with PID) is done with the program, for example:
    "CHILD <16741> process has done with testalphabet program !"
    
 4) The messages should match the real execution orders, i.e. when the testspecial program starts/ends, the right message should be print out. So you need to figure out how to get the starting/ending time of each 
 process.
   
   
 The expected screen print out should be similar as follows:
 
 CHILD <16741> process is executing testalphabet program!
 CHILD <16742> process is executing testspecial program!
, -> 745668
. -> 798072
... ...

CHILD <16742> process has done with testspecial program !
a -> 2973036
b -> 556908
... ...

CHILD <16741> process has done with testalphabet program !
 */


int main( int argc, char *argv[] )
{       
    pid_t pid1;
    pid_t pid2;
    int status1;
    int status2;

    pid1 = fork();

    if ( pid1 < 0 ) //The creation of child process is unsuccessful 
    {
        perror( "ERROR! Fork failed!" ); 
        exit(1);
    }

    if ( pid1 == 0 )
    {
        // The newly created child

        printf( "CHILD <PID: %d> process is executing testspecial program!\n", getpid() );

        char *specialchar[] = { "./testspecial" , NULL };
        execv( specialchar[0], specialchar );   //execute the path of the executable file.
    }

    if ( pid1 > 0 )
    {
      
        pid2 = fork();

        if ( pid2 == 0 )
        {
            // ANOTHER CHILD PROCESS CREATED

            printf( "CHILD <PID: %d> process is executing testalphabet program!\n", getpid() );

            char *alphabetchar[] = { "./testalphabet" , NULL };
            execv( alphabetchar[0], alphabetchar); //execute the path of the executable file.
      
        }

        else if ( pid2 > 0 )
        {

            // if child1 terminated...

            if ( waitpid( pid1, &status1, 0 ) == pid1 ) //wait for pid1 to end 
            {
                printf( "CHILD <PID: %d> process has done with testspecial program! See the results above!\n", getpid() );
            }

            // if child2 terminated...

            if ( waitpid( pid2, &status2, 0 ) == pid2 ) //wait for pid2 to end 
            {
                printf( "CHILD <PID: %d> process has done with testalphabet program! See the results above!\n", getpid() );
            }
        }

    }


    return 0;
    
}
