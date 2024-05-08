/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 07:10:32 by danevans          #+#    #+#             */
/*   Updated: 2024/05/08 18:32:50 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_image_error(t_data *data)
{
	if (!data->floor)
		ft_error_exit(data, "FLOOR_XPM error\n");
	if (!data->wall)
		ft_error_exit(data, "WALL_XPM error\n");
	if (!data->coin)
		ft_error_exit(data, "COIN_XPM error\n");
	if (!data->player)
		ft_error_exit(data, "PLAYER_XPM error\n");
	if (!data->exit)
		ft_error_exit(data, "EXIT_XPM error\n");
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

void	ft_image_window(t_data *data, int x, int y, char *image)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		image, x * TILE_SIZE, y * TILE_SIZE);
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
				ft_image_window(data, x, y, data->wall);
			else if (data->map.map[y][x] == '0')
				ft_image_window(data, x, y, data->floor);
			else if (data->map.map[y][x] == 'P')
				ft_image_window(data, x, y, data->player);
			else if (data->map.map[y][x] == 'C')
				ft_image_window(data, x, y, data->coin);
			else if (data->map.map[y][x] == 'E')
				ft_image_window(data, x, y, data->exit);
		}
	}
}
