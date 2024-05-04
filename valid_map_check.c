/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:49:33 by danevans          #+#    #+#             */
/*   Updated: 2024/05/04 10:06:20 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			if ((data->map.map[i][j] != 'E') && (data->map.map[i][j] != 'P') &&
				(data->map.map[i][j] != 'C')
				&& (data->map.map[i][j] != '0') && (data->map.map[i][j] != '1'))
				{
					printf("what is wrong %c,  %d   %d\n", data->map.map[i][j], i, j);
					ft_error_exit(NULL, "Invalid format_check_element", 1);
				}
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
		ft_error_exit(NULL, "Invalid No collectable", 1);
	if ((data->map.exit > 1) || (data->map.exit == 0))
		ft_error_exit(NULL, "Invalid Mutiple Exit", 1);
	if ((data->map.player > 1) || (data->map.player == 0))
		ft_error_exit(NULL, "Invalid Num of Players", 1);
	i = -1;
	while (++i < data->map.column)
		if ((data->map.map[0][i] != '1') &&
			(data->map.map[data->map.row - 1][i] != '1'))
			ft_error_exit(NULL, "Invalid ! Map should be guided", 1);
	i = -1;
	while (++i < data->map.row) 
		if ((data->map.map[i][0] != '1') &&
			(data->map.map[i][data->map.column - 1] != '1'))
			ft_error_exit(NULL, "Invalid ! Map should be guided", 1);
}

// bool	ft_flood_fill(t_data *data, char **dup_map, t_pos curr_pos)
// {
// 	int		coin;
// 	bool	exit;

// 	coin = 0;
// 	exit = false;
// 	printf("did you get here x = %d   y = %d\n", data->map.curr_pos.x, data->map.curr_pos.y);
// 	if (dup_map[curr_pos.y][curr_pos.x] == '1')
// 		return (false);
// 	else if (dup_map[curr_pos.y][curr_pos.x] == 'C')
// 		coin++;
// 	else if (dup_map[curr_pos.y][curr_pos.x] == 'E')
// 		exit = true;
// 	dup_map[curr_pos.y][curr_pos.x] = '1';
// 	ft_flood_fill(data, dup_map, (t_pos){curr_pos.x + 1, curr_pos.y});
// 	ft_flood_fill(data, dup_map, (t_pos){curr_pos.x - 1, curr_pos.y});
// 	ft_flood_fill(data, dup_map, (t_pos){curr_pos.x, curr_pos.y - 1});
// 	ft_flood_fill(data, dup_map, (t_pos){curr_pos.x, curr_pos.y + 1});
// 	printf("did you get here and pass hehre\n");
// 	if (coin == data->map.collectable && exit == true)
// 		return (true);
// 	return (false);
// }

bool ft_flood_fill(t_data *data, char **dup_map, t_pos curr_pos) {
    // Check boundaries
    if (curr_pos.x < 0 || curr_pos.x >= data->map.column || curr_pos.y < 0 || curr_pos.y >= data->map.row) {
        return false;  // Out of bounds
    }

    // Check if the current position is already visited or is a wall
    if (dup_map[curr_pos.y][curr_pos.x] == '1') {
        return false;  // Already visited or is a wall
    }

    // Process current cell
    bool isExit = (dup_map[curr_pos.y][curr_pos.x] == 'E');
    bool isCoin = (dup_map[curr_pos.y][curr_pos.x] == 'C');
    dup_map[curr_pos.y][curr_pos.x] = '1';  // Mark as visited

    // Recurse to neighboring cells
    bool down = ft_flood_fill(data, dup_map, (t_pos){curr_pos.x, curr_pos.y + 1});
    bool up = ft_flood_fill(data, dup_map, (t_pos){curr_pos.x, curr_pos.y - 1});
    bool right = ft_flood_fill(data, dup_map, (t_pos){curr_pos.x + 1, curr_pos.y});
    bool left = ft_flood_fill(data, dup_map, (t_pos){curr_pos.x - 1, curr_pos.y});

    // Combine results
    return (isExit && isCoin) || down || up || right || left;
}


void	ft_valid_path_check(t_data *data)
{
	char	**dup_map;

	ft_check_element(data);
	ft_check_wall_wrong_info(data);
	dup_map = ft_create_dup_map(data);
	bool result = ft_flood_fill(data, dup_map, data->map.curr_pos);
	if (!result)
	{
		free_matrix(dup_map);
		ft_error_exit(data, "Invalid Path not found", 1);
	}
	free_matrix(dup_map);
	
		
}