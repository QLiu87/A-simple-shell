#include "Command_S.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
int Command_S::execute(){
    char *argv[3];
    argv[0] = executable;
    argv[1] = arg;
    argv[2] = NULL;
    pid_t pid = fork();
    if(pid > 0) {
        waitpid(pid,NULL,0);
    }
    else if(pid == 0){ 
        if( execvp(argv[0], argv) < 0){ 
            perror("Error ");
            return 0;
        }
    }
    else { 
        perror("Error ");
        return 0;
    }
   return 1;
}
