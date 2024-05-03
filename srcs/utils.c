/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 00:32:33 by danevans          #+#    #+#             */
/*   Updated: 2024/05/04 00:52:37 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
			ft_free_matrix(dup_map);
			ft_error_exit(data, "Malloc failed");
		}
	}
	dup_map[i] = NULL;
	return(dup_map);
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