NAME = so_long

CC = gcc

# INCLUDES = -I/usr/include -Imlx1
CFLAGS = -Wall -Wextra -Werror -I.
MLXFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

GRAPHICS = $(wildcard srcs/graphics/*.c)
MAP = $(wildcard srcs/map/*.c)
UTILS = $(wildcard srcs/*.c)

MINILIBX = mlx/
LIBFT = comb_libf/

SOURCE = $(GRAPHICS) $(MAP) $(UTILS)

all: $(NAME)

$(NAME):
	make -C $(MINILIBX)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(SOURCE) $(MLXFLAGS) -L$(LIBFT) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	make clean -C $(MINILIBX)
	make clean -C $(LIBFT)

fclean: clean
		rm -rf $(NAME)

re: fclean all