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

// read_line function to read a line of input from stdin



// exit status function

int exit_status(void)
{
    int status;
    if (WIFEXITED(status))
    {
        status = WEXITSTATUS(status);
    }
    return status;
}

// execute function to execute the command

int execute(char **args)
{
    int i = 0;
    if (args[0] == NULL)
    {
        // An empty command was entered.
        return 1;
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        // exit command
        return 0;
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        // cd command
        if (args[1] == NULL)
        {
            fprintf(stderr, "myshell: expected argument to \"cd\"\n");
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("myshell");
            }
        }
        return 1;
    }
    else if (strcmp(args[0], "history") == 0)
    {
        // history command
        FILE *fp;
        fp = fopen("history.txt", "r");
        char c;
        c = fgetc(fp);
        while (c != EOF)
        {
            printf("%c", c);
            c = fgetc(fp);
        }
        fclose(fp);
        return 1;
    }
    else
    {
        // fork() creates a new process
        pid_t pid = fork();
        if (pid == 0)
        {
            // child process
            if (execvp(args[0], args) == -1)
            {
                perror("myshell");
            }
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            // error forking
            perror("myshell");
        }
        else
        {
            // parent process
            wait(NULL);
        }
        return 1;
    }
}

// PATH handling

void path_handling(char **args){
    char *path = getenv("PATH");
    char *path_tokens[MAX_NUM_PATHS];
    int i = 0;
    path_tokens[i] = strtok(path, ":");
    while(path_tokens[i] != NULL){
        i++;
        path_tokens[i] = strtok(NULL, ":");
    }
    i = 0;
    while(path_tokens[i] != NULL){
        char *path = path_tokens[i];
        strcat(path, "/");
        strcat(path, args[0]);
        execvp(path, args);
        i++;
    }
}

// Cat Command


// History Command

void history_command(char *command){
    FILE *fp;
    fp = fopen("history.txt", "a");
    fprintf(fp, "%s\n", command);
    fclose(fp);
}

// git add * command   

void git_add_command(char *command){
    FILE *fp;
    fp = fopen("history.txt", "a");
    fprintf(fp, "%s\n", command);
    fclose(fp);

    char *args[] = {"git", "add", "*", NULL};
    pid_t pid = fork();

    // if (pid == 0)
    // {
    //     // child process
    //     if (execvp(args[0], args) == -1)
    //     {
    //         perror("myshell");
    //     }
    //     exit(EXIT_FAILURE);
    // }
    // else if (pid < 0)
    // {
    //     // error forking
    //     perror("myshell");
    // }
    // else
    // {
    //     // parent process
    //     wait(NULL);
    // }
    // return 1;

    // git commit -m "message" command

    // void git_commit(char *command){

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

        // change directory

        if (strcmp(command, "cd") == 0) {
            char *home = getenv("HOME");
            chdir(home);
            continue;
        }

        // change directory to specified directory

        if (strncmp(command, "cd ", 3) == 0) {
            char *path = command + 3;
            chdir(path);
            continue;
        }


        // history command

        if (strcmp(command, "history") == 0) {
            FILE *fp;
            fp = fopen("history.txt", "r");
            char c;
            c = fgetc(fp);
            while (c != EOF)
            {
                printf("%c", c);
                c = fgetc(fp);
            }
            fclose(fp);
            continue;
        }

        

        // exit status

        if (strcmp(command, "exit status") == 0) {
            printf("%d\n", exit_status());
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

        // set environment variables

        if (strcmp(command, "setenv") == 0) {
            system("set");
            continue;
        }

        // print user id

        if (strcmp(command, "id") == 0) {
            system("id");
            continue;
        }

        // USER environment variable

        if (strcmp(command, "USER") == 0) {
            system("USER");
            continue;
        }

        // unset environment variables

        if (strcmp(command, "unsetenv") == 0) {
            system("unset");
            continue;
        }

        // print current date and time

        if (strcmp(command, "date") == 0) {
            system("date");
            continue;
        }

        // print current date and time in UTC

        if (strcmp(command, "date -u") == 0) {
            system("date -u");
            continue;
        }

        // TAB completion

        if (strcmp(command, "TAB") == 0) {
            system("TAB");
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