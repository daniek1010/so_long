# NAME = so_long

# CC = gcc

# MINILIBX := mlx/
# LIBFT := ./comb_libft/
# LIBFTPRINT := libftprint.a

# INCLUDES = -I./comb_libft

# CFLAGS := -Wall -Wextra -Werror -I.

# MLXFLAGS := -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

# SOURCE := $(wildcard *.c)

# all: $(NAME)

# $(NAME):
# 	make -C $(MINILIBX)
# 	make -C $(LIBFT)
# 	$(CC) $(CFLAGS) $(SOURCE) $(MLXFLAGS)  -L$(LIBFTPRINT) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# clean:
# 	make clean -C $(MINILIBX)
# 	make clean -C $(LIBFT)

# fclean: clean
# 		rm -rf $(NAME)

# re: fclean all


NAME = so_long

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -I./comb_libft

MLXFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

MINILIBX = mlx/
LIBFT = ./comb_libft/
LIBFTPRINT = ./comb_libft/libftprintf.a # Assuming the library name is libftprint.a, adjust if different

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
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
