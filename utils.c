/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 00:32:33 by danevans          #+#    #+#             */
/*   Updated: 2024/05/06 08:23:51 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_matrix(char *str[])
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_create_dup_map(t_data *data)
{
	int		i;
	char	**dup_map;

	dup_map = malloc ((data->map.row + 1) * (sizeof(char *)));
	if (!dup_map)
		ft_error_exit(data, "Malloc Failed");
	i = -1;
	while (++i < data->map.row)
	{
		dup_map[i] = ft_strdup(data->map.map[i]);
		if (!dup_map)
		{
			free_matrix(dup_map);
			ft_error_exit(data, "Malloc failed");
		}
	}
	dup_map[i] = NULL;
	return (dup_map);
}

void	ft_write(t_data *data, int x, int counter)
{
	if (x == 1)
		ft_printf("You won! Congrats!!\n");
	else if (x == 2)
		ft_printf("Moves: %d\n", counter);
	else if (x == 3)
		ft_printf("collectable Remaining: %d\n", data->map.collectable);
}

void	ft_destroy(t_data *data)
{
	if (data->floor)
		mlx_destroy_image(data->mlx_ptr, data->floor);
	if (data->wall)
		mlx_destroy_image(data->mlx_ptr, data->wall);
	if (data->coin)
		mlx_destroy_image(data->mlx_ptr, data->coin);
	if (data->player)
		mlx_destroy_image(data->mlx_ptr, data->player);
	if (data->exit)
		mlx_destroy_image(data->mlx_ptr, data->exit);
	if (data->mlx_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data->map.map)
		free_matrix(data->map.map);
}

void	ft_error_exit(t_data *data, char *str)
{
	if (data)
		ft_destroy(data);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}
