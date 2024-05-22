NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC =  parsing.c philo.c utilis.c
HEADER = philo.h
OBJ = $(SRC:.c=.o)

all: $(NAME)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
