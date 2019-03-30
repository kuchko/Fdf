#include "fdf.h"

void		ft_move_wire(t_wire *w)
{
	int		y;
	int		x;

	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			w->nods[y][x].x += w->x_bias;
			w->nods[y][x].y += w->y_bias;
		}
	}
}

void		ft_zoom_wire(t_wire *w)
{
	int		y;
	int		x;

	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			w->nods[y][x].x = w->nods[y][x].x * w->zoom;
			w->nods[y][x].y = w->nods[y][x].y * w->zoom;
			w->nods[y][x].z = w->nods[y][x].z * w->zoom;
		}
	}
}

static void	ft_rotate_nod(t_wire *w, t_iso *iso, int y, int x)
{
	double	pre;

	if (iso->x != 0.0)
	{
		pre = w->nods[y][x].y;
		w->nods[y][x].y = w->nods[y][x].y * cos(iso->x) +
												w->nods[y][x].z * sin(iso->x);
		w->nods[y][x].z = -pre * sin(iso->x) + w->nods[y][x].z * cos(iso->x);
	}
	if (iso->y != 0.0)
	{
		pre = w->nods[y][x].x;
		w->nods[y][x].x = w->nods[y][x].x * cos(iso->y) +
												w->nods[y][x].z * sin(iso->y);
		w->nods[y][x].z = -pre * sin(iso->y) + w->nods[y][x].z * cos(iso->y);
	}
	if (iso->z != 0.0)
	{
		pre = w->nods[y][x].x;
		w->nods[y][x].x = w->nods[y][x].x * cos(iso->z) -
												w->nods[y][x].y * sin(iso->z);
		w->nods[y][x].y = pre * sin(iso->z) + w->nods[y][x].y * cos(iso->z);
	}
}

void		ft_rotate_wire(t_wire *w, t_iso *iso)
{
	int		y;
	int		x;

	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			ft_rotate_nod(w, iso, y, x);
		}
	}
}
