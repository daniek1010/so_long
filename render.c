/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 07:10:32 by danevans          #+#    #+#             */
/*   Updated: 2024/05/04 07:33:00 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_image_error(t_data *data)
{
	if (!data->floor)
		ft_error_exit(data, "FLOOR_XPM error", 0);
	if (!data->wall)
		ft_error_exit(data, "WALL_XPM error", 0);
	if (!data->coin)
		ft_error_exit(data, "COIN_XPM error", 0);
	if (!data->player)
		ft_error_exit(data, "PLAYER_XPM error", 0);
	if (!data->exit)
		ft_error_exit(data, "EXIT_XPM error", 0);
}

static void	ft_open_image(t_data *data)
{
	int	tile_width;
	int	tile_height;

	data->floor = mlx_xpm_file_to_image(data->mlx_ptr, FLOOR_TILE,
			&tile_width, &tile_height);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, WALL_TILE,
			&tile_width, &tile_height);
	data->coin = mlx_xpm_file_to_image(data->mlx_ptr, COLLECTABLE_TILE,
			&tile_width, &tile_height);
	data->player = mlx_xpm_file_to_image(data->mlx_ptr, PLAYER_TILE,
			&tile_width, &tile_height);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr, EXIT_TILE,
			&tile_width, &tile_height);
	ft_image_error(data);
	
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


