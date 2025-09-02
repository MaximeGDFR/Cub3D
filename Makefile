NAME        = cub3d

# DIRECTORIES
RM          =	rm -f
SRC_DIR     =	./src
OBJ_DIR     =	.obj
SRCS        =	$(SRC_DIR)/main.c \
				$(SRC_DIR)/floodfil.c \
				$(SRC_DIR)/parsing.c \
				$(SRC_DIR)/read_map.c \
				$(SRC_DIR)/utils.c

# INCLUDES
LIBFT_DIR   = ./libft
MLX_DIR     = ./minilibx-linux
LIBFT       = $(OBJ_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a

# FLAGS
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(MLX_DIR) -g
MLXFLAGS    = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# OBJECTS
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# BUILDING RULES
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(OBJ_DIR) -l:libft.a $(MLXFLAGS) -o $@

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT): $(OBJ_DIR)
	make -s -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a $(OBJ_DIR)/libft.a

clean:
	make -s -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)/libft.a

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re