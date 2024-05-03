#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>

#include "./so_long.h"
 
// typedef struct s_data
// {
// 	void *mlx_ptr;
// 	void *win_ptr;
// } t_data;

char	*tile_filename = "./tile.xpm";
int		tile_width = 100;
int		tile_height = 100;
 

 
int on_keypress(int keysym, t_data *data)
{
	(void)
	printf("Pressed key: %d\\n", keysym);
	fflush(stdout);
	if (keysym == 65307)
	{
		on_destroy(data);
	}
	return (0);
}

int ft_destroy(t_data *data)
{
	
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	//return (0);
}

void ft_error_exit(t_data *data, char *str)
{
	ft_destory(data)  //todo
	ft_putstr_fd(str, 1); //todo && need to include my libft
	exit(0);
}

void	ft_check_args(int argc, char *argv[])
{
	if (argc != 2)
		ft_error_exit(NULL, "Invalid args");
	if (argv[1] == '\0')
		ft_error_exit(NULL, "No Map found");
}
 
int main(int argc, char *argv[])
{
	t_data data;

	ft_check_args(argc, argv);
	ft_map_structure(&data, argv[1]); //todo
	ft_valid_map_check(&data);
	ft_valid_path_check(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		ft_error_exit(data, "Failed mlx init");	
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map.row * TILE_SIZE,
		data.map.column * TILE_SIZE, "so_long");
	if (!data.win_ptr)
		ft_error_exit(data, "Failed Windows create");
	ft_render_screen(&data);
	

	char *image = mlx_xpm_file_to_image(data.mlx_ptr, tile_filename, &tile_width, &tile_height);

	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, (void*)(image), 200, 300);

	// Register key release hook
	mlx_key_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
 
	// Register destroy hook
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
 
	// Loop over the MLX pointer
	mlx_loop(data.mlx_ptr);

	
	//on_destroy(&data);
	return (0);
}
