NAME = get_next_line.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = get_next_line.c get_next_line_utils.c

SRC_OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_OBJ)
	ar -rc $(NAME) $(SRC_OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(SRC_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all