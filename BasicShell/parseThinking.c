#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_NUM_ARGS 64

int main(int argc, char **argv){
    char command[MAX_INPUT_SIZE];
    char *args[MAX_NUM_ARGS];
    char *path = getenv("PATH");
    char *token = strtok(path, ":");
    char *path_array[100];
    int i = 0;
    while(token != NULL){
        path_array[i] = token;
        token = strtok(NULL, ":");
        i++;
    }
    path_array[i] = NULL;
    while(1) {
        printf("# ");

        // read command from stdin
        if (fgets(command, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("Error reading command\n");
            continue;
        }

        // Remove trailing newline
        size_t length = strlen(command);
        if (command[length - 1] == '\n') {
            command[length - 1] = '\0';
        }
        // Exit if the user entered "exit"
        if (strcmp(command, "exit") == 0) {
            break;
        }
        // Parse the command and arguments
        parse_command(command, args);
        // Fork a child process
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(args[0], args);
            // If execvp returns, it must have failed
            printf("Unknown command\n");
            exit(0);
        } else {
            // Parent process
            wait(NULL);
        }
    }
    return 0;
}