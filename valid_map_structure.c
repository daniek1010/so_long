/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 06:26:29 by danevans          #+#    #+#             */
/*   Updated: 2024/05/04 09:19:58 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	valid_extension(char *str)
{
	int		len;

	len = ft_strlen(str) - 4;
	if (ft_strncmp(".ber", str + len, 4))
		return (0);
	return (1);
}

static void ft_row_check(t_data *data, char *str)
{
    int		fd;
    int		counter;
    char    *temp;
	
	fd = open(str, O_RDONLY);
	if (fd < 1)
        ft_error_exit(NULL, "Couldn't Open file", 2);
	counter = 0;
    temp = get_next_line(fd);
	while (temp != NULL)
	{
		counter++;
		free(temp);
		temp = get_next_line(fd);	
	}
	if (counter == 0)
		ft_error_exit(NULL, "Invalid single row", 2);
    data->map.row = counter;
    close (fd);
	return;
}

static void ft_add_line(t_data *data, char *str)
{
    int		fd;
    int		i;
	
	fd = open(str, O_RDONLY);
	if (fd < 1)
        ft_error_exit(NULL, "Couldn't Open file", 2);
	i = 0;
    data->map.map[i] = get_next_line(fd);
	while (i < data->map.row)
		data->map.map[++i] = get_next_line(fd);
	data->map.map[i] = NULL;
	data->map.column = ft_strlen(data->map.map[0]);
	i = 0;
	while (data->map.map[i] != NULL)
	{
		if (data->map.column != (int)ft_strlen(data->map.map[i]))
			ft_error_exit(NULL, "Invalid rectangular map fmt only", 1);
		i++;
	}
	close (fd);
}

int ft_valid_map_check(t_data *data, char *str)
{
	if (!valid_extension(str))
		ft_error_exit(NULL, "Invalid file", 2);
    ft_row_check(data, str);
	data->map.map = malloc((data->map.row + 1 ) * (sizeof(char *)));
	ft_add_line(data, str);
	return (1);
}
