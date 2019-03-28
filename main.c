// gcc -I minilibx testing.c -L minilibx -lmlx -framework OpenGL -framework AppKit
//man /Users/okuchko/Desktop/fdf/minilibx/man/man3/mlx.1
#include "fdf.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	t_list	*start;
	t_fdf	f;
//	t_iso	iso;

	ft_printf("get ready ........\n");
	ft_read(&f.w_orig, &start, argc, argv);
	ft_fdf_init(&f);
	//ft_fit_wire(&f, &f.orig);
	// ft_copy_wire(&wire, &wire_2);
	//ft_show_wire_coordinates(&f.w_orig);


	// ft_rotate_wire(&wire, &wire_2, &f, &iso);
	// ft_move_wire(&wire_2, f.img_high /2 , f.img_width / 2);
	ft_printf("Ready to play!!!\n");
	ft_draw(&f);

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

