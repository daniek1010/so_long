/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 03:59:16 by danevans          #+#    #+#             */
/*   Updated: 2024/05/08 04:05:06 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_exit(t_data *data, int y_axis, int x_axis, int new)
{
	if (data->map.collectable != 0)
	{
		ft_check_postion(data, y_axis, x_axis);
		data->map.map[y_axis][new] = '0';
		ft_image_window(data, new, y_axis, data->floor);
		data->flag2 = true;
		return (0);
	}
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->player, x_axis * TILE_SIZE,
		y_axis * TILE_SIZE);
	ft_write(data, 1, 0);
	ft_destroy(data);
	exit (0);
}

int	ft_check_exit_w(t_data *data, int y_axis, int x_axis, int new)
{
	if (data->map.collectable != 0)
	{
		ft_check_postion(data, y_axis, x_axis);
		data->map.map[new][x_axis] = '0';
		ft_image_window(data, x_axis, new, data->floor);
		data->flag2 = true;
		return (0);
	}
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->player, x_axis * TILE_SIZE,
		y_axis * TILE_SIZE);
	ft_write(data, 1, 0);
	ft_destroy(data);
	exit (0);
}

void	ft_update_tiles(t_data *data, int y_axis, int x_axis, char tile)
{
	if (tile == 'E')
	{
		data->map.map[y_axis][x_axis] = tile;
		ft_image_window(data, x_axis, y_axis, data->exit);
	}
	else if (tile == '0')
	{
		data->map.map[y_axis][x_axis] = tile;
		ft_image_window(data, x_axis, y_axis, data->floor);
	}
}
