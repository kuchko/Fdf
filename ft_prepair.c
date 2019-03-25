#include "fdf.h"

void	ft_f_init(t_fdf *f)
{
	f->win_width = 1600;
	f->win_high = 1000;
	f->img_width = 1600;
	f->img_high = 1000;
}

void	ft_fit_wire(t_fdf *f, t_wire *w)
{
	int del;
	int y;
	int x;

	del = w->x_range > w->y_range ? w->x_range : w->y_range;
	ft_printf("w->x_range = %d, w->y_range = %d,  del = %d\n", w->x_range,w->y_range, del);
	w->dx = del < (f->img_width / 2) ? f->img_width / 2 / del : 1;
	w->dy = w->dx;
	w->dz_mult = w->z_range < f->img_high / 6 ? (f->img_high / 6 )/ w->z_range : 1;
	w->dz_div = w->z_range > f->img_high ? w->z_range / f->img_high: 1;
	ft_printf("w->dx = %d, w->dy = %d, dz_mult = %d, dz_div = %d\n", w->dx, w->dy, w->dz_mult, w->dz_div);
	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			w->nods[y][x].x = w->nods[y][x].x * w->dx - w->dx * w->x_range / 2;
			w->nods[y][x].y = w->nods[y][x].y * w->dy - w->dy * w->y_range / 2;
			w->nods[y][x].z = (w->nods[y][x].z * w->dz_mult) / w->dz_div;
		}
	}
}

int	ft_copy_wire(t_wire *w1, t_wire *w2)
{
	int y;
	int x;

	w2->x_range = w1->x_range;
	w2->y_range = w1->y_range;
	w2->z_range = w1->z_range;
	w2->z_min = w1->z_min;
	w2->z_max = w1->z_max;
	w2->dx = w1->dx;
	w2->dy = w1->dy;
	w2->dz_div = w1->dz_div;
	w2->dz_mult = w1->dz_mult;
	if(!(w2->nods = (t_nod**)ft_double_malloc(sizeof(t_nod), w1->y_range, w1->x_range)))
		return (0);
	y = -1;
	while (++y < w1->y_range)
	{
		x = -1;
		while (++x < w1->x_range)
		{
			w2->nods[y][x].y = w1->nods[y][x].y;
			w2->nods[y][x].x = w1->nods[y][x].x;
			w2->nods[y][x].z = w1->nods[y][x].z;
			w2->nods[y][x].argb = w1->nods[y][x].argb;
		}
	}
	return (1);
}
