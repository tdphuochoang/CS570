#include <stdio.h>

#include <unistd.h>

main(int argc, char **argv){       

        int i;       

        for (i=0; i < 3; i++)

        {               

                fork();               

                printf("hello\n");       

        }

}