/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 08:20:25 by danevans          #+#    #+#             */
/*   Updated: 2024/05/06 08:23:19 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_args(int argc, char *argv[])
{
	if (argc != 2)
		ft_error_exit(NULL, "Invalid args");
	if (argv[1][0] == '\0')
		ft_error_exit(NULL, "No map file");
}

int	on_destroy(t_data *data)
{
	ft_destroy(data);
	ft_putstr_fd("Exit", 1);
	exit (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data.flag = false;
	ft_check_args(argc, argv);
	ft_valid_map_check(&data, argv[1]);
	ft_valid_path_check(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		ft_error_exit(&data, "Failed mlx init");
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map.column * TILE_SIZE,
			data.map.row * TILE_SIZE, "so_long");
	if (!data.win_ptr)
		ft_error_exit(&data, "Failed Windows create");
	ft_render_screen(&data);
	mlx_key_hook(data.win_ptr, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask,
		&on_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
