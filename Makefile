NAME		= 	cub3d

# DIRECTORIES
RM			= 	rm -f
SRC_DIR		= 	./src
SRCS		= 	$(SRC_DIR)/main.c

# INCLUDES
LIBFT_DIR	= ./libft
MLX_DIR		= ./minilibx-linux
LIBFT		= $(LIBFT_DIR)/libft.a

# FLAGS
CC			= cc
# CFLAGS		+= -fsanitize=address
CFLAGS		= -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(MLX_DIR) -g
MLXFLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# OBJECTS
OBJS		= $(SRCS:.c=.o)

# BUILDING RULES
all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -libft $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	make -s -C $(LIBFT_DIR)

clean:
	make -s -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re