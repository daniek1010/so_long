NAME := so_long

CC := gcc
INCLUDES = -I/usr/include -Imlx1
CFLAGS := -Wall -Wextra -Werror

SOURCE := main.c
LIBRARY := -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
MINILIBX := mlx/

all:
	make -C $(MINILIBX)
	$(CC) $(CFLAGS) $(SOURCE) $(INCLUDES) $(LIBRARY) -o $(NAME)

clean:

fclean: clean
		make clean -C $(MINILIBX)
		rm -rf $(NAME)

re: fclean all