#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"



// initialize the shell
// Parse the command and arguments
// use string library for functions
// strcmp, strlen, strcpy, strtok, etc.
// use stdlib.h for exit
// use stdio.h for printf, fgets, etc.
// use stdio.h for ls, pwd, etc.

// use unistd.h for fork, execvp, etc.
// use sys/wait.h for wait
// handle exit command ctrl+d
// handle the PATH variable
//handle special characters: ", ', <, >, |, &, ;,&,#,%,@,!,^,*,(,),{,},[,],?,~,`,\,=,_,+,-,.,/

// print the welcome message






// parse the command and arguments

void parse_command(char *command, char **args){
    int i = 0;
    while(command[i] != '\0'){
        if(command[i] == ' '){
            command[i] = '\0';
            args++;
        }
        else{
            *args = command + i;
        }
        i++;
    }
    *args = '\0';
}


int main(int argc, char **argv){
    char command[MAX_INPUT_SIZE];
    printf("%s", WELCOME_MSG);
    
    while(1) {
        // printf("%s", WELCOME_MSG);
        printf("%s", PROMPT);

        // read command from stdin
        if (fgets(command, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("Error reading command\n");
            continue;
        }

        // Remove trailing newline
        size_t length = strlen(command);
        if (command[length - 1] == '\n') {
            command[length - 1] = '\0';

        
        // Exit if the user entered "exit"

        
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // clear the screen

        if (strcmp(command, "clear") == 0) {
            system("clear");
            continue;
        }

        // list files in current directory

        if (strcmp(command, "ls") == 0) {
            system("ls");
            continue;
        }

        // ls -al

        if (strcmp(command, "ls -al") == 0) {
            system("ls -al");
            continue;
        }


        // list all files in current directory

        if (strcmp(command, "ls -a") == 0) {
            system("ls -a");
            continue;
        }

        // list all files in current directory with long format

        if (strcmp(command, "ls -l") == 0) {
            system("ls -l");
            continue;
        }

        // print working directory

        if (strcmp(command, "pwd") == 0) {
            system("pwd");
            continue;
        }

        // git status

        if (strcmp(command, "git status") == 0) {
            system("git status");
            continue;
        }

        // git add

        if (strcmp(command, "git add") == 0) {
            system("git add");
            continue;
        }

        // git commit

        if (strcmp(command, "git commit") == 0) {
            system("git commit");
            continue;
        }

        // git push

        if (strcmp(command, "git push") == 0) {
            system("git push");
            continue;
        }

        // git pull

        if (strcmp(command, "git pull") == 0) {
            system("git pull");
            continue;
        }

        // git fetch

        if (strcmp(command, "git fetch") == 0) {
            system("git fetch");
            continue;
        }
        

        // print environment variables

        if (strcmp(command, "env") == 0) {
            system("env");
            continue;
        }

        // who am i

        if (strcmp(command, "whoami") == 0) {
            system("whoami");
            continue;
        }

        // parse and execute command
        char *args[MAX_INPUT_SIZE / 2 + 1];
        parse_command(command, args);
        pid_t pid = fork();
        if (pid == 0) {
            // child process
            execvp(args[0], args);
            printf("Error executing command\n");
            exit(1);
        } else if (pid > 0) {
            // parent process
            wait(NULL);
        } else {
            // fork failed
            printf("Error forking\n");
            exit(1);
        }

    

    // Parse and execute command
    // Exit if the user entered "exit"

    }
    }
        // exit the shell message

        printf("%s", EXIT_MSG);

        return 0;
}