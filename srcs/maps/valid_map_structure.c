/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 06:26:29 by danevans          #+#    #+#             */
/*   Updated: 2024/05/02 12:39:31 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	valid_extension(char *str)
{
	int		len;

	len = ft_strlen(str) - 4;
	if (ft_strncmp(".ber", str[len], 4))
		return (0);
	return (1);
}

static void ft_row_check(t_data *data, char *str)
{
    int		fd;
    int		counter;
    char    *temp;
	
	if (fd = open(str, O_RDONLY) < 1)
        ft_error_exit(NULL, "Couldn't Open file");
	counter = 0;
    temp = get_next_line(fd);
	while (temp != NULL)
	{
		counter++;
		free(temp);
		temp = get_next_line(fd);
		
	}
	
	if (counter == 0)
		ft_error_exit(NULL, "Invalid single row");
    data->map.row = counter;
    close (fd);
	return ;
}

static void ft_add_line(t_data *data, char *str)
{
    int		fd;
    int		i;
    char    *temp;
	
	if (fd = open(str, O_RDONLY) < 1)
        ft_error_exit(NULL, "Couldn't Open file");
	i = 0;
    data->map.map[i] = get_next_line(fd);
	while (data->map.map[i] != NULL)
		data->map.map[++i] = get_next_line(fd);
	data->map.map[i] = NULL;
	//possible error based on size if '\n' char is needed for the size or not;
	data->map.column = ft_strlen(data->map.map[0]);
	i = 0;
	while (data->map.map[i] != NULL)
	{
		if (data->map.column != data->map.map[i]) // need to update error to take care of the **map
			ft_error_exit(data, "Invalid format");
		i++;
	}
	close (fd);
}

int ft_valid_map_check(t_data *data, char *str)
{
    int     fd;
    int     counter;
    char    *str;

	if (!valid_extension(str))
		ft_error_exit(NULL, "Invalid file");
    ft_row_check(data, str);
	data->map.map = malloc((data->map.row + 1 ) * (sizeof(char *)));
	ft_add_line(data, str);
}

void	ft_image_error(t_data *data)
{
	if (!data->floor)
		ft_error_exit(data, "FLOOR_XPM error");
	if (!data->wall)
		ft_error_exit(data, "WALL_XPM error");
	if (!data->coin)
		ft_error_exit(data, "COIN_XPM error");
	if (!data->player)
		ft_error_exit(data, "PLAYER_XPM error");
	if (!data->exit)
		ft_error_exit(data, "EXIT_XPM error");
}
