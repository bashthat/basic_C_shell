#include "shell.h"
char *read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us
    getline(&line, &bufsize, stdin);
    return line;
}

// split_line function to split the line into tokens

char **split_line(char *line)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    // if memory allocation fails
    if (!tokens)
    {
        fprintf(stderr, "myshell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // strtok() splits the string into tokens
    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        // if the number of tokens exceeds the buffer size
        if (position >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            // if memory allocation fails
            if (!tokens)
            {
                fprintf(stderr, "myshell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
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

// main function

int main(int argc, char **argv)
{
    // read_line() reads a line of input from stdin
    char *line;
    // split_line() splits the line into tokens
    char **args;
    // execute() executes the command
    int status;

    do
    {
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

