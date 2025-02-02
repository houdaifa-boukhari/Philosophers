NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
SRC =  parsing.c philo.c utilis.c utilis1.c actions.c
HEADER = philo.h
OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
