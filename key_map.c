/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:35:30 by danevans          #+#    #+#             */
/*   Updated: 2024/05/06 08:18:57 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_check_postion(t_data *data, int y_axis, int x_axis)
{
	static int	counter = 0;

	if (data->map.map[y_axis][x_axis] == 'C')
	{
		data->map.collectable--;
		counter++;
		data->map.curr_pos = (t_pos){x_axis, y_axis};
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->player, x_axis * TILE_SIZE,
			y_axis * TILE_SIZE);
		ft_write(data, 2, counter);
		ft_write(data, 3, 0);
	}
	else if (data->map.map[y_axis][x_axis] == '0')
	{
		counter++;
		data->map.curr_pos = (t_pos){x_axis, y_axis};
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->player, x_axis * TILE_SIZE,
			y_axis * TILE_SIZE);
		ft_write(data, 2, counter);
	}
	return (0);
}

static int	ft_check_exit(t_data *data, int y_axis, int x_axis)
{
	if (data->map.collectable != 0)
		return (1);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->player, x_axis * TILE_SIZE,
		y_axis * TILE_SIZE);
	ft_write(data, 1, 0);
	ft_destroy(data);
	exit (0);
}

static int	ft_vertical_w_s(t_data *data, char c)
{
	int	x_axis;
	int	y_axis;
	int	new_y;

	x_axis = data->map.curr_pos.x;
	y_axis = data->map.curr_pos.y;
	if (c == 'w')
		new_y = y_axis--;
	else
		new_y = y_axis++;
	if (data->map.map[y_axis][x_axis] == '1')
		return (1);
	if (data->map.map[y_axis][x_axis] == 'E')
	{
		if (!ft_check_exit(data, y_axis, x_axis))
			return (1);
	}
	else
	{
		ft_check_postion(data, y_axis, x_axis);
		data->map.map[new_y][x_axis] = '0';
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, x_axis * TILE_SIZE, new_y * TILE_SIZE);
	}
	return (0);
}

static int	ft_horizontal_a_d(t_data *data, char c)
{
	int	x_axis;
	int	y_axis;
	int	new_x;

	x_axis = data->map.curr_pos.x;
	y_axis = data->map.curr_pos.y;
	if (c == 'a')
		new_x = x_axis--;
	else
		new_x = x_axis++;
	if (data->map.map[y_axis][x_axis] == '1')
		return (1);
	if (data->map.map[y_axis][x_axis] == 'E')
	{
		if (!ft_check_exit(data, y_axis, x_axis))
			return (1);
	}
	else
	{
		ft_check_postion(data, y_axis, x_axis);
		data->map.map[y_axis][new_x] = '0';
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor, new_x * TILE_SIZE, y_axis * TILE_SIZE);
	}
	return (0);
}

int	on_keypress(int key, t_data *data)
{
	if (key == XK_Escape)
		on_destroy(data);
	else if ((key == 'w') || (key == XK_Up))
		ft_vertical_w_s(data, 'w');
	else if ((key == 's') || (key == XK_Down))
		ft_vertical_w_s(data, 's');
	else if ((key == 'a') || (key == XK_Left))
		ft_horizontal_a_d(data, 'a');
	else if ((key == 'd') || (key == XK_Right))
		ft_horizontal_a_d(data, 'd');
	return (1);
}
