#include "shell.h"

void execute_command(char *command) {
    /*
     * handle_exit - exit code to execute a command
     *
     * run_shell - execute a command
     * Return:0
     */
    printf("Executing command: %s\n", command);
}

void handle_exit(void) {
    printf("Exiting the shell\n");
    exit(EXIT_SUCCESS);
}

void run_shell(void) {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("SimpleShell> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        // Remove the  newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Check for the exit command
        if (strcmp(input, "exit") == 0) {
            handle_exit();
        }

        // Execute the command
        execute_command(input);
    }
}

int main(void) {
    run_shell();
    return 0;
}
