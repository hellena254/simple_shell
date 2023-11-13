#include <stdio.h>
#include<shell.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGUMENTS 10


/**
 * *token  - tokenizes the input
 * @command: the command line to tokenize
 * @args: An array to store the command and its arguments
 * @arg_count: pointer to the count of arguments in the array
 */
int main(void) {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        // Display prompt
        printf("simple_shell> ");

        // Read input from user
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            // Handle EOF (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Tokenize the input
        char *args[MAX_ARGUMENTS];
        char *token = strtok(input, " ");
        int i = 0;

        while (token != NULL && i < MAX_ARGUMENTS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL; 
       	// Set the last element to NULL for execvp

        // Check if the command exists in the current directory
        if (access(args[0], X_OK) == 0) {
            // Fork a new process
            pid_t pid = fork();

            if (pid == -1) {
                // Fork failed
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process

                // Execute the command using execvp
                if (execvp(args[0], args) == -1) {
                    // Print error message if execvp fails
                    perror("Command not found");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process

                // Wait for the child process to finish
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) {
                    // Handle error in child process
                    printf("Error executing command: %s\n", args[0]);
                }
            }
        } else {
            // Command not found in the current directory, search in PATH
            char *path = getenv("PATH");
            if (path != NULL) {
                char *path_copy = strdup(path);
                char *dir = strtok(path_copy, ":");

                while (dir != NULL) {
                    char full_path[MAX_INPUT_LENGTH];
                    snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);

                    if (access(full_path, X_OK) == 0) {
                        // Fork a new process
                        pid_t pid = fork();

                        if (pid == -1) {
                            // Fork failed
                            perror("Fork failed");
                            exit(EXIT_FAILURE);
                        } else if (pid == 0) {
                            // Child process

                            // Execute the command using execvp
                            if (execvp(full_path, args) == -1) {
                                // Print error message if execvp fails
                                perror("Command not found");
                                exit(EXIT_FAILURE);
                            }
                        } else {
                            // Parent process

                            // Wait for the child process to finish
                            int status;
                            waitpid(pid, &status, 0);

                            if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) {
                                // Handle error in child process
                                printf("Error executing command: %s\n", args[0]);
                            }

                            // Break out of the loop since command is found and executed
                            break;
                        }
                    }

                    dir = strtok(NULL, ":");
                }

                free(path_copy);
            } else {
                printf("PATH environment variable not set.\n");
            }
        }
    }

    return 0;
}
