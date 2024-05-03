#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "./so_long.h"
 
void	ft_destroy(t_data *data)
{
	if (data == NULL)
		return ;	
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

void ft_error_exit(t_data *data, char *str)
{
	ft_destory(data);
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	exit(0);
}

void	ft_check_args(int argc, char *argv[])
{
	if (argc != 2)
		ft_error_exit(NULL, "Invalid args");
	if (argv[1] == '\0')
		ft_error_exit(NULL, "No map file");
}
 
int main(int argc, char *argv[])
{
	t_data data;

	ft_check_args(argc, argv);
	ft_valid_map_check(&data, argv[1]);
	ft_valid_path_check(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		ft_error_exit(data, "Failed mlx init");	
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map.row * TILE_SIZE,
		data.map.column * TILE_SIZE, "so_long");
	if (!data.win_ptr)
		ft_error_exit(data, "Failed Windows create");
	ft_render_screen(&data);
	mlx_key_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &destroy, data);
	mlx_loop(&data);
	return (0);
}
