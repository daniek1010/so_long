/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 06:26:29 by danevans          #+#    #+#             */
/*   Updated: 2024/05/08 19:09:42 by danevans         ###   ########.fr       */
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

static void	ft_row_check(t_data *data, char *str)
{
	int		fd;
	int		counter;
	char	*temp;

	fd = open(str, O_RDONLY);
	if (fd < 1)
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
	close(fd);
	return ;
}

static void	ft_add_line(t_data *data, char *str)
{
	int		fd;
	int		i;

	fd = open(str, O_RDONLY);
	if (fd < 1)
		ft_error_exit(data, "Couldn't Open file");
	i = -1;
	while (++i < data->map.row)
		data->map.map[i] = get_next_line(fd);
	data->map.map[i] = NULL;
	close(fd);
	i = 0;
	while (i < data->map.row)
	{
		data->map.map[i] = trim_free(data->map.map[i], "\n");
		if (!data->map.map[i])
			ft_error_exit(data, "Failed here\n");
		i++;
	}
	data->map.column = ft_strlen(data->map.map[0]);
}

static void	ft_map_len(t_data *data)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(data->map.map[0]);
	while (++i < data->map.row)
	{
		if (len != ft_strlen(data->map.map[i]))
			ft_error_exit(data, "INvalid Map\n");
	}
}

int	ft_valid_map_check(t_data *data, char *str)
{
	if (!valid_extension(str))
		ft_error_exit(NULL, "Invalid file\n");
	ft_row_check(data, str);
	data->map.map = malloc((data->map.row + 1) * (sizeof(char *)));
	ft_add_line(data, str);
	ft_map_len(data);
	return (0);
}
