#include "shell.h"

// prompt and read/write/execute commands from user input

int main (void)
{
    // read_line() reads a line of input from stdin
    char *line;
    // split_line() splits the line into tokens
    char **args;
    // execute() executes the command
    int status;

    do {
        printf("%s", PROMPT);
        line = read_line();
        args = split_line(line);
        status = execute(args);

        // free memory
        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}
