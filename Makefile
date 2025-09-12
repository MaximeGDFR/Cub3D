NAME        = cub3d

# DIRECTORIES
RM          = rm -f
SRC_DIR     = ./src
OBJ_DIR     = .obj
SRCS        = $(SRC_DIR)/main.c \
              $(SRC_DIR)/utils.c \
              $(SRC_DIR)/mapcheck/extend_map.c \
              $(SRC_DIR)/mapcheck/floodfill.c \
              $(SRC_DIR)/mapcheck/print_map.c \
              $(SRC_DIR)/parsing/init.c \
              $(SRC_DIR)/parsing/parse_color.c \
              $(SRC_DIR)/parsing/parse_map.c \
              $(SRC_DIR)/parsing/parse_texture.c \
              $(SRC_DIR)/parsing/parsing_utils.c \
              $(SRC_DIR)/parsing/parsing.c

# INCLUDES
LIBFT_DIR   = ./libft
MLX_DIR     = ./minilibx-linux
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

# FLAGS
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(MLX_DIR) -g
MLXFLAGS    = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# OBJECTS
OBJS        = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# BUILDING RULES
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $@

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -s -C $(LIBFT_DIR)

clean:
	make -s -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
