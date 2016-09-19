#include "lab4.h"

// Execute a command with optional wait
int runcommand(char** cline, int where)
{
    pid_t pid;
    int status;

    /* Bug 2 - implement the cd function 
    * The way that this worked was to get the user input from cline and 
    * feed it through as a string. This works by comparing what the cline
    * input was to the string "cd" and anything that comes after cd, if 
    * the user wanted to go to another directory other than home. 
    * First, it checks if it is cd, then, it checks if what comes after
    * cd is nothing, or new line character, if it is, then it goes to the home
    * directory via the "chdir" command. The getev("HOME") is what tells chdir
    * where to go. If what comes after cd isn't blank and is actually a directory,
    * then chdir will go there instead. This directory is achieved through cline+3, which is
    * literally just the cline character after cd. To check if the directory exists or not
    * we use getenv(). If it does not, we print out to the user that it does not.
    */

    if (strcmp(*cline,"cd")==0){
        if(strcmp(*cline+3, "\n")==0){
            chdir(getenv("HOME"));
        }
        else{

            if (chdir(*cline+3)== 0){
                chdir(*cline+3);                
            }
            else{
                printf("directory does not exist\n");
            }
        }
      
    }

    /* Bug 3
    * implement "exit" feature
    * this feature is implemented similar to cd in that it first uses
    * strcmp to check if the input matches a certain string. This time, 
    * it checks if it matches "exit". If it does, then we just want to use
    * the command exit() to exit the shell. We put 0 because we want to indicate
    * that is is a "normal" exit. 
    */
    else if (strcmp(*cline, "exit")==0){
        
        exit(0);
    
    }
    else{

        int child_status; 

        switch(pid = fork())
        {

            case -1:
                perror(SHELL_NAME);
                return (-1);
            case 0:
                
                execvp(*cline,cline);
                //we should never get to this code, sice execve does not return
                perror(*cline);
                exit(1);
            
            /* Bug 5
            * The bug was that it supports running processes in the background
            * but it does not reap the processes correctly so zombie processes 
            * are produced. The fix here is to add a default to the switch statements
            * so that the parent can wait for the child process status and 
            * when the child process terminates, it will reap the child process so that
            * it won't be a zombie. 
            */
            default:
      
             wait(&child_status);
            
        }
}

    // Code for parent
    // If background process print pid and exit program is running in the background
    if(where == BACKGROUND)
    {
        printf("[Process id %d]\n",pid);
        return 0;
    }

    // Wait until process pid exits
    if (waitpid(pid,&status,0) == -1) 
    {
        return -1;
    } 
    else 
    {
        return status;
    }
}
