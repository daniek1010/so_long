/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 07:10:32 by danevans          #+#    #+#             */
/*   Updated: 2024/05/03 12:10:17 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_image_error(t_data *data)
{
	if (!data->floor)
		ft_error_exit(data, "FLOOR_XPM error");
	if (!data->wall)
		ft_error_exit(data, "WALL_XPM error");
	if (!data->coin)
		ft_error_exit(data, "COIN_XPM error");
	if (!data->player)
		ft_error_exit(data, "PLAYER_XPM error");
	if (!data->exit)
		ft_error_exit(data, "EXIT_XPM error");
}

static void	ft_open_image(t_data *data)
{
	int	tile_width;
	int	tile_height;

	data->floor = mlx_xpm_file_to_image(data.mlx_ptr, FLOOR_TILE,
			&tile_width, &tile_height);
	data->wall = mlx_xpm_file_to_image(data.mlx_ptr, WALL_TILE,
			&tile_width, &tile_height);
	data->coin = mlx_xpm_file_to_image(data.mlx_ptr, COLLECTABLE_TILE,
			&tile_width, &tile_height);
	data->player = mlx_xpm_file_to_image(data.mlx_ptr, PLAYER_TILE,
			&tile_width, &tile_height);
	data->exit = mlx_xpm_file_to_image(data.mlx_ptr, EXIT_TILE,
			&tile_width, &tile_height);
}

void	ft_render_screen(t_data *data)
{
	int	x;
	int	y;

	ft_open_image(data);
	y = -1;
	while (++y < data->map.row)
	{
		x = -1;
		while (++x < data->map.column)
		{
			if (data->map.map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map.map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->floor, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map.map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr,
					data->win_ptr, data->player, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map.map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->coin, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map.map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->exit, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
}

void	ft_check_postion(t_data *data, int key)
{
	data->map.curr_pos
}

void	ft_check_tile_update(t-data *data, int key)
{
	ft_check_postion(data, key);
	ft_update_postion(data);
}

int on_keypress(int key, t_data *data)
{
	if (key == XK_Escape)
	else if (key == W) || (key == XK_Up)
		ft_check_tile_update(data, key);
	else if (key == S) || (key == XK_Down)
		ft_check_tile_update(data);
	else if (key == A) || (key == XK_Left)
		ft_check_tile_update(data);
	else if (key == D) || (key == XK_Down)
		ft_check_tile_update(data);
	(void)
	printf("Pressed key: %d\\n", keysym);
	fflush(stdout);
	if (keysym == 65307)
	{
		on_destroy(data);
	}
	return (0);
}
