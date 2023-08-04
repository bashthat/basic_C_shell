#ifndef SHELL_H_INCLUDED
#define SHELL_H_INCLUDED

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_NUM_ARGS 64
#define MAX_NUM_PATHS 100
#define MAX_HISTORY_SIZE 100
#define PROMPT ANSI_COLOR_CYAN "myshell> " ANSI_COLOR_RESET
#define HISTORY_PROMPT "history> "
#define HISTORY_FILE ".myshell_history"
#define WELCOME_MSG ANSI_COLOR_MAGENTA "Welcome to myshell!\nType exit to exit the shell\n\n\n=============================================\n\nPLEASE LEAVE A REVIEW!!\nTHANKS FOR TESTING!!\n=============================================\n" ANSI_COLOR_RESET
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

/* Functions and Prototypes */

void init_shell();
void print_prompt();
/* Cleanup Function */
void cleanup();
/*Signal Handling*/
void sigintHandler(int sig_num);
/* Read Command */
char* read_command();
/* void read_command(char* cmd); */

#endif // SHELL_H_INCLUDED