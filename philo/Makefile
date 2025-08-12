NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SOURCES = main.c parsing.c utils.c init.c simulation.c actions.c cleanup.c monitor.c
OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re