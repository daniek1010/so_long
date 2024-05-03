/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:35:30 by danevans          #+#    #+#             */
/*   Updated: 2024/05/04 00:45:26 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_check_postion(t_data *data, int x_axis, int y_axis)
{
	if (data-map.map[y_axis][x_axis] == 'E')
	{
		if (data->collectable == 0)
		{
			ft_write(data, 1);
			return (0);
		}
		return (1);
	}
	else if (data-map.map[y_axis][x_axis] == 'C')
	{
		data->map.collectable--;
		data->map.counter++;
		data->map.curr_pos = (t_pos) {y_axis, x_axis};
		ft_write(data, 2);
		ft_write(data, 3);
	}
	else if (data-map.map[y_axis][x_axis] == '0')
	{
		data->map.counter++;
		data->map.curr_pos = (t_pos) {y_axis, x_axis};
		ft_write(data, 3);
	}
	return (0);
}

int	ft_vertical_w_s(t_data *data, char c)
{
	int	x_axis;
	int	y_axis;

	x_axis = data->curr_pos.x;
	y_axis = data->curr_pos.y;
	if (c == 'w')
		y_axis--;
	else
		x_axis++;
	if (data->map.map[y_axis][x_axis] != '1')
		return(ft_check_postion(data, x_axis, y_axis));
	return (1);
}

int	ft_horizontal_a_d(t_data *data, char c)
{
	int	x_axis;
	int	y_axis;

	x_axis = data->curr_pos.x;
	y_axis = data->curr_pos.y;
	if (c == 'a')
		x_axis--;
	else
		x_axis++;
	if (data->map.map[y_axis][x_axis] != '1')
		return (ft_check_postion(data, x_axis, y_axis));
	return (1);
}

int	on_destroy(t_data *data, int key)
{
	ft_error_exit(data, "Exit");
}

int on_keypress(t_data *data, int key)
{
	if (key == XK_Escape)
		on_destroy(data, key);
	else if (key == 'W') || (key == XK_Up)
		ft_vertical_w_s(data, 'w');
	else if (key == 'S') || (key == XK_Down)
		ft_vertical_w_s(data, 's');
	else if (key == 'A') || (key == XK_Left)
		ft_horizontal_a_d(data, 'a');
	else if (key == 'D') || (key == XK_Right)
		ft_horizontal_a_d(data, 'd');
	return (1);
}