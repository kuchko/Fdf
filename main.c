// gcc -I minilibx testing.c -L minilibx -lmlx -framework OpenGL -framework AppKit
//man /Users/okuchko/Desktop/fdf/minilibx/man/man3/mlx.1
#include "fdf.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	int		fd;
	t_list	*start;
	t_wire	wire;

	if (argc == 1 && ft_printf("usage:	fdf map_file\n"))
		return (0);
	if (argc > 2 && ft_printf("fdf must have only one map_file\n"))
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) == -1 &&
								ft_printf("open map_file error\n"))
		return (0);
	if ((wire.y_range = ft_read_to_list(&start, fd)) == 0)
		return (0);
	if(ft_valid_symbols(start, wire.y_range) == 0)
		return (0);

	ft_printf("map_looks like valid\n");

	ft_make_valid_wire(start, &wire);

	ft_show_wire_coordinates(&wire);
	// ft_printf("%d\n", ft_atoi_base_positiv("0000FF", 16));
	// t_list *tmp;

	// tmp = start;

	// while (tmp)
	// {
	// 	ft_printf("%s\n", tmp->content);
	// 	tmp = tmp->next;
	// }

	close(fd);
	system("leaks fdf > leaks.txt");
	return(0);
}

void	ft_show_wire_coordinates(t_wire *w)
{
	int i;
	int j;

	j = -1;
	while (++j < w->y_range)
	{
		i = -1;
		while (++i < w->x_range)
			ft_printf("%10d", w->nods[j][i].x);
		ft_printf("\n");
		i = -1;
		while (++i < w->x_range)
			ft_printf("%10d", w->nods[j][i].y);
		ft_printf("\n");
		while (++i < w->x_range)
			ft_printf("%10d", w->nods[j][i].z);
		ft_printf("\n");
		while (++i < w->x_range)
			ft_printf("%#10X", w->nods[j][i].argb);
		ft_printf("\n");
		ft_printf("\n");
	}
}

/*
int deal_key(int key, void *param)
{
	if (key == 53)
		exit(0);
	ft_printf("%d \n", key);
	return(0);
}

int main()
{
	int i;

	void	*mlx_ptr;
	void	*win_ptr;

	i = -1;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 640, 480, "First window");
	while (++i < 100)
		mlx_pixel_put(mlx_ptr, win_ptr, 150 + i, 100 + i/2, 0xFFFFFF);
	mlx_string_put(mlx_ptr, win_ptr, 150, 100, 0xFFFFFF, "xXXx");
	mlx_key_hook(win_ptr, deal_key, (void*)0);
	mlx_loop(mlx_ptr);
	return (0);

}
*/
