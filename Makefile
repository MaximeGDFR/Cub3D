NAME		= 	cub3d
RM			= 	rm -f
SRC_DIR		= 	./src
SRCS		= 	$(SRC_DIR)/main.c

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(LIBFT_DIR) -g
# CFLAGS		+= -fsanitize=address
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft-complete -o $(NAME)

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