# --- Program Name ---
NAME = cub3D

# --- Compiler and Flags ---
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# --- Library Folders ---
LIBFT_DIR = ./libft
GNL_DIR   = ./get_next_line
MLX_DIR   = ./minilibx-linux

# --- Your Project Source Files ---
# Just list the .c file names. 'make' will find them.
SRC_FILES = cub3d.c \
			parsing.c \
			initializations.c \
			cleanup.c \
			render_hook.c \
			get_next_line.c \
			get_next_line_utils.c

# --- Tell 'make' where to look for .c files ---
vpath %.c .:cub3d:$(GNL_DIR)

# --- Object Files (all .o files will be in the root) ---
OBJS = $(SRC_FILES:.c=.o)

# --- Library Files ---
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

# --- Linker Flags (MLX, X11, Math) ---
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

# --- Include Paths ---
INCLUDES = -I. -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)

# --- Main Rule ---
all: $(NAME)

# --- Rule to build your program ---
$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# --- Rule to build Libft ---
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

# --- Rule to compile .c to .o ---
# This one rule now works for all .c files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# --- Clean Rules ---
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re