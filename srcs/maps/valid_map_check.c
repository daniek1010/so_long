/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:49:33 by danevans          #+#    #+#             */
/*   Updated: 2024/05/04 00:48:56 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	ft_data_init(t_data *data)
{
	data->map.exit = 0;
	data->map.collectable = 0;
	data->map.player = 0;
}

static void	ft_check_element(t_data *data)
{
	int	i;
	int	j;

	ft_data_init(data);
	i = -1;
	while (++i < data->map.row)
	{
		j = -1;
		while (++j < data->map.column)
		{
			if (data->map.map[i][j] != 'E'|| data->map.map[i][j] != 'P'||
				data->map.map[i][j] != 'C' 
				|| data->map.map[i][j] != '0' || data->map.map[i][j] != '1')
					ft_error_exit(data, "Invalid format");
			if (data->map.map[i][j] == 'E')
				data->map.exit++;
			else if (data->map.map[i][j] == 'C')
				data->map.collectable++;
			else if (data->map.map[i][j] == 'P') //here was used to determine player position;
			{
				data->map.player++;
				data->map.curr_pos = (t_pos) {j, i};
			}
		}
	}
}

static void	ft_check_wall_wrong_info(t_data *data)
{
	//just checking if all contain wall and then if this contains if more than one start and exit and player
	int		i;

	if (data->map.collectable == 0)
		ft_error_exit(data "Invalid No collectable");
	if ((data->map.exit > 1) || (data->map.exit == 0))
		ft_error_exit(data "Invalid Mutiple Exit");
	if ((data->map.player > 1) || (data->map.player == 0))
		ft_error_exit(data "Invalid Num of Players");
	i = -1;
	while (++i < data->map.column)
		if ((data->map.map[0][i] != '1') &&
			(data->map.map[data->map.row - 1][i] != '1'))
			ft_error_exit(data, "Invalid ! Map should be guided");
	i = -1;
	while (++i < data->map.row) 
		if ((data->map.map[i][0] != '1') &&
			(data->map.map[i][data->map.column - 1] != '1'))
			ft_error_exit(data, "Invalid ! Map should be guided");
}

bool	ft_flood_fill(t_data *data, char **dup_map, t_pos curr_pos)
{
	int		coin;
	bool	exit;

	coin = 0;
	exit = false;
	if (dup_map[curr_pos.y][curr_pos.x] == '1')
		return (false);
	else if (dup_map[curr_pos.y][curr_pos.x] == 'C')
		coin++;
	else if (dup_map[curr_pos.y][curr_pos.x] == 'E')
		exit = true;
	dup_map[curr_pos.y][curr_pos.x] = '1';
	ft_flood_fill(data, dup_map, (t_pos){curr_pos[x - 1][y]});
	ft_flood_fill(data, dup_map, (t_pos){curr_pos[x + 1][y]});
	ft_flood_fill(data, dup_map, (t_pos){curr_pos[x][y - 1]});
	ft_flood_fill(data, dup_map, (t_pos){curr_pos[x][y + 1]});
	if (coin == data->map.collectable && exit == true)
		return (true);
}

void	ft_valid_path_check(t_data *data)
{
	char	**dup_map;

	ft_check_element(data);
	ft_check_wall_wrong_info(data);
	dup_map = ft_create_dup_map(data);
	if (ft_flood_fill(data, dup_map, data->map.curr_pos) == false)
		ft_error_exit(data, "Invalid Path not found");
}