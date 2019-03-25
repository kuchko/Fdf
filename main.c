// gcc -I minilibx testing.c -L minilibx -lmlx -framework OpenGL -framework AppKit
//man /Users/okuchko/Desktop/fdf/minilibx/man/man3/mlx.1
#include "fdf.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	t_wire	wire;
	t_wire	wire_2;
	t_list	*start;
	t_fdf	f;


	ft_read(&wire, &start, argc, argv);
	ft_f_init(&f);
	ft_fit_wire(&f, &wire);
	ft_copy_wire(&wire, &wire_2);
	ft_show_wire_coordinates(&wire_2);
	ft_draw(&wire_2, &f);

	system("leaks fdf > leaks.txt");
	return(0);
}

void	ft_show_list(t_list *lst)
{
	while(lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
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
		i = -1;
		while (++i < w->x_range)
			ft_printf("%10d", w->nods[j][i].z);
		ft_printf("\n");
		i = -1;
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
