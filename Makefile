NAME = so_long

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I. -I./comb_libft

MLXFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

MINILIBX = mlx/
LIBFT = ./comb_libft/
LIBFTPRINT = ./comb_libft/libftprintf.a

SOURCE = $(wildcard *.c)

all: $(NAME)

$(NAME):
	make -C $(MINILIBX)
	make -C $(LIBFT)
	$(CC)  $(CFLAGS) $(SOURCE) $(MLXFLAGS) $(LIBFTPRINT) -o $(NAME)

clean:
	make clean -C $(MINILIBX)
	make clean -C $(LIBFT)
	rm -f *.o

fclean: clean
	make fclean -C $(LIBFT)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
