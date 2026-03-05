NAME = philo

SRC = main.c helper.c philo.c prep_struct.c print.c thread_handling.c reaper.c protect_free.c

CC = cc
FLAG = -Wall -Werror -Wextra 

HEAD = philo.h
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) -lpthread $(OBJ) -o $(NAME)

%.o: %.c $(HEAD)
	$(CC) $(FLAG) -c -pthread $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re