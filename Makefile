NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

LIBFT_DIR = ./libft
MLX_DIR   = ./minilibx-linux

SRC_FILES = cub3d.c \
			parser.c \
			initializations.c \
			cleanup.c \
			render_hook.c \
			./get_next_line/get_next_line.c \
			./get_next_line/get_next_line_utils.c

OBJS = $(SRC_FILES:.c=.o)

LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

INCLUDES = -I. -I$(MLX_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re