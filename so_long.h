/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 05:52:10 by danevans          #+#    #+#             */
/*   Updated: 2024/05/04 00:52:49 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H

# define SO_LONG_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "mlx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

#include "./comb_libft/ft_printf.h"

# define TILE_SIZE 32;

# define WALL_TILE "./game_images/wall.xpm"
# define FLOOR_TILE "./game_images/floor.xpm"
# define PLAYER_TILE "./game_images/player.xpm"
# define COLLECTABLE_TILE "./game_images/coins.xpm"
# define EXIT_TILE "./game_images/exit.xpm"


typedef struct	s_pos
{
	int		x;
	int		y;
}
t_pos;

typedef struct s_map
{
    int		row;
    int		column;
	int		collectable;
	int		counter;
	int		exit;
	int		player;
	int		start;
    char	**map;
	t_pos	curr_pos;
    
}t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*floor;
	void	*wall;
	void	*exit;
	void	*coin;
	void	*player;
	t_map	map;
	
} t_data;

void ft_error_exit(t_data *data, char *str);

/* valid_map_check.c */
void	ft_valid_path_check(t_data *data);

void	ft_render_screen(t_data *data);

/* valid_map_structure.c */
void	ft_image_error(t_data *data)
int		ft_valid_map_check(t_data *data, char *str);

/* utils.c */
char	**ft_create_dup_map(t_data *data);
void	ft_write(t_data *data, int x);











#endif