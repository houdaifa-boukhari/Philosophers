NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -fsanitize=thread
SRC =  parsing.c philo.c utilis.c
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
