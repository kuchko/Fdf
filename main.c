#include "fdf.h"

int		main(int argc, char **argv)
{
	t_list	*start;
	t_fdf	f;

	ft_printf("Get Ready 3! 2! 1!...\n");
	ft_read(&f.w_orig, &start, argc, argv);
	ft_fdf_init(&f);
	ft_printf("Enjoy!!!\n");
	ft_draw(&f);
	system("leaks fdf > leaks");
	return (0);
}

void	ft_show_list(t_list *lst)
{
	while (lst)
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
		ft_printf("\n\n");
	}
}
