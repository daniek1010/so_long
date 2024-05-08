/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:35:30 by danevans          #+#    #+#             */
/*   Updated: 2024/05/08 04:03:36 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_postion(t_data *data, int y_axis, int x_axis)
{
	static int	counter = 0;

	if (data->map.map[y_axis][x_axis] == 'C')
	{
		data->map.collectable--;
		counter++;
		data->map.curr_pos = (t_pos){x_axis, y_axis};
		ft_image_window(data, x_axis, y_axis, data->player);
		ft_write(data, 3, counter);
	}
	else if (data->map.map[y_axis][x_axis] == '0')
	{
		counter++;
		data->map.curr_pos = (t_pos){x_axis, y_axis};
		ft_image_window(data, x_axis, y_axis, data->player);
		ft_write(data, 2, counter);
	}
	else if (data->map.map[y_axis][x_axis] == 'E')
	{
		counter++;
		data->map.curr_pos = (t_pos){x_axis, y_axis};
		ft_image_window(data, x_axis, y_axis, data->player);
		ft_write(data, 2, counter);
	}
	return (0);
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
		ft_check_exit_w(data, y_axis, x_axis, new_y);
	else
	{
		ft_check_postion(data, y_axis, x_axis);
		if (data->flag2)
			ft_update_tiles(data, new_y, x_axis, 'E');
		else
			ft_update_tiles(data, new_y, x_axis, '0');
		data->flag2 = false;
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
		ft_check_exit(data, y_axis, x_axis, new_x);
	else
	{
		ft_check_postion(data, y_axis, x_axis);
		if (data->flag2)
			ft_update_tiles(data, y_axis, new_x, 'E');
		else
			ft_update_tiles(data, y_axis, new_x, '0');
		data->flag2 = false;
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
