#include "fdf.h"

void		ft_color_by_z(t_wire *w)
{
	int		y;
	int		x;
	t_nod	n1;
	t_nod	n2;
	t_nod	n3;

	n1.argb = 0x0000ff;
	n2.argb = 0xb22222;
	n3.argb = 0xadff2f;
	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			if (w->nods[y][x].z < 0 && w->z_min != 0)
				w->nods[y][x].argb = ft_aprox_color(n2, n1,
						(double)w->nods[y][x].z / (double)w->z_min);
			if (w->nods[y][x].z == 0)
				w->nods[y][x].argb = n2.argb;
			if (w->nods[y][x].z > 0 && w->z_max != 0)
				w->nods[y][x].argb = ft_aprox_color(n2, n3,
						(double)w->nods[y][x].z / (double)w->z_max);
		}
	}
}

void		ft_color_fill(t_wire *w, int color)
{
	int		y;
	int		x;

	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
			w->nods[y][x].argb = color;
	}
}

void		ft_iso_wire(t_wire *w1)
{
	int		y;
	int		x;
	int		y_pre;
	int		x_pre;

	y = -1;
	while (++y < w1->y_range)
	{
		x = -1;
		while (++x < w1->x_range)
		{
			x_pre = w1->nods[y][x].x;
			y_pre = w1->nods[y][x].y;
			w1->nods[y][x].x = (x_pre - y_pre) * cos(0.523599);
			w1->nods[y][x].y = (x_pre + y_pre) * sin(0.523599)
												- w1->nods[y][x].z;
		}
	}
}

void		ft_perspective_wire(t_wire *w1)
{
	int		y;
	int		x;
	int		max;
	double	dist;

	max = w1->x_range > w1->y_range ? w1->x_range : w1->y_range;
	dist = max > 800 ? -max * 1.5 : -600.0;
	dist *= w1->zoom;
	y = -1;
	while (++y < w1->y_range)
	{
		x = -1;
		while (++x < w1->x_range)
		{
			if (w1->nods[y][x].z != dist)
			{
				w1->nods[y][x].x = w1->nods[y][x].x /
								(1 + w1->nods[y][x].z / dist);
				w1->nods[y][x].y = w1->nods[y][x].y /
								(1 + w1->nods[y][x].z / dist);
			}
		}
	}
}
