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

#include "shell.h"

/**
 * tokenize_command - tokenizes a command line into an array of strings
 * @command: the command line to tokenize
 * @args: An array to store the command and its arguments
 * @arg_count: pointer to the count of arguments in the array
 */
void tokenize_command(char *command, char *args[], size_t *arg_count)
{
    char *token = strtok(command, " ");

    while (token != NULL && *arg_count < MAX_ARGS - 1)
    {
        args[(*arg_count)++] = token;
        token = strtok(NULL, " ");
    }
    /* null-terminate the array*/
    args[*arg_count] = NULL;
}

/**
 * execute_child - execute the command in the child process
 * @args: An array containing the command and its arguments
 */
void execute_child(char *args[])
{
    execvp(args[0], args);
    _error("No such file or directory");
    exit(EXIT_FAILURE);
}

/**
 * execute_parent - waits for the child process to finish in the parent process
 * @pid_child: The pid of the child process
 * @status: Pointer to store the exit status of the child process
 */
void execute_parent(pid_t pid_child, int *status)
{
    waitpid(pid_child, status, 0);
}

/**
 * execute_command - executes command entered by the user
 * @command: command entered by the user
 *
 * Return: SHELL_EXIT if command is exit otherwise SHELL_SUCCESS
 */
int execute_command(char *command)
{
    if (strcmp(command, "exit") == 0)
        return (SHELL_EXIT);

    size_t arg_count = 0;
    char *args[MAX_ARGS];

    tokenize_command(command, args, &arg_count);

    // Check if the command exists in the current directory
    if (access(args[0], X_OK) == 0)
    {
        pid_t pid_child = fork();
        if (pid_child == -1)
        {
            /* fork failed*/
            _error("failed to create child process");
            return (SHELL_SUCCESS);
        }

        if (pid_child == 0)
        {
            /* child process*/
            execute_child(args);
        }
        else
        {
            /* parent process*/
            execute_parent(pid_child, NULL);
        }
    }
    else
    {
        // Command not found in the current directory, search in PATH
        char *path = getenv("PATH");
        if (path != NULL)
        {
            char *path_copy = strdup(path);
            char *dir = strtok(path_copy, ":");

            while (dir != NULL)
            {
                char full_path[MAX_INPUT_LENGTH];
                snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);

                if (access(full_path, X_OK) == 0)
                {
                    pid_t pid_child = fork();
                    if (pid_child == -1)
                    {
                        /* fork failed*/
                        _error("failed to create child process");
                        free(path_copy);
                        return (SHELL_SUCCESS);
                    }

                    if (pid_child == 0)
                    {
                        /* child process*/
                        execute_child(args);
                    }
                    else
                    {
                        /* parent process*/
                        execute_parent(pid_child, NULL);
                        free(path_copy);
                        return (SHELL_SUCCESS);
                    }
                }

                dir = strtok(NULL, ":");
            }

            free(path_copy);
        }
        else
        {
            _error("PATH environment variable not set.");
        }
    }

    return (SHELL_SUCCESS);
}
