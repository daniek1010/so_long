/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 00:32:33 by danevans          #+#    #+#             */
/*   Updated: 2024/05/05 17:21:59 by danevans         ###   ########.fr       */
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
		ft_error_exit(data, "Malloc Failed", 2);
	i = -1;
	while (++i < data->map.row)
	{
		dup_map[i] = ft_strdup(data->map.map[i]);
		if (!dup_map)
		{
			free_matrix(dup_map);
			ft_error_exit(data, "Malloc failed", 2);
		}
	}
	dup_map[i] = NULL;
	return (dup_map);
}

void	ft_write(t_data *data, int x)
{
	if (x == 1)
		ft_printf("YOu won!\n");
	else if (x == 2)
		ft_printf("Moves: %d\n", data->map.counter);
	else if (x == 3)
		ft_printf("collectable Remaining: %d\n", data->map.collectable);
}

void	ft_destroy(t_data *data)
{
	if (data == NULL)
		return ;
	ft_putstr_fd("ThIst\n", 2);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

void	ft_error_exit(t_data *data, char *str, int x)
{
	ft_putstr_fd("ThIs is aanother test %d\n", 2);
	printf("x == %d\n", x);
	if (x == 0)
	{
		free_matrix(data->map.map);
		ft_destroy(data);
	}
	else if (x == 1)
		ft_putstr_fd("ThIs is aanother test %d\n", 2);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	exit(0);
}
