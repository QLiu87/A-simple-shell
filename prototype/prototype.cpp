#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void prototype(){
    char *argv[3];
    argv[0] = "/bin/ls";
    argv[1] = "-la";
    argv[2] = NULL;
    pid_t pid = fork();
    
    if(pid > 0) {
        waitpid();
    }
    else if(pid == 0){ 
        if( execvp(argv[0], argv) <0){ 
            perr(“Error “);
        }
    }
    else { 
        perror(“Error “);
    }
}

