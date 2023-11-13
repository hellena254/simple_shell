CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c shell.c execute_command.c readline.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = shell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
		 $(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re
