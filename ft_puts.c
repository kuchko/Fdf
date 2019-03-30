#include "fdf.h"

static int	ft_get_light(int start, int end, double perc)
{
	return ((int)((1 - perc) * start + perc * end));
}

int			ft_aprox_color(t_nod n1, t_nod n2, double perc)
{
	int	r;
	int	g;
	int	b;

	r = ft_get_light((n1.argb >> 16) & 0xFF, (n2.argb >> 16) & 0xFF, perc);
	g = ft_get_light((n1.argb >> 8) & 0xFF, (n2.argb >> 8) & 0xFF, perc);
	b = ft_get_light(n1.argb & 0xFF, n2.argb & 0xFF, perc);
	return ((r << 16) | (g << 8) | b);
}

void		ft_putpixel(t_fdf *f, int x, int y, int color)
{
	int	*i;

	if (x > -1 && x < f->win_width && y > -1 && y < f->win_high)
	{
		i = (int*)f->adr;
		i[y * f->img_width + x] = color;
	}
}

void		ft_putline(t_fdf *f, t_nod n1, t_nod n2)
{
	int	delta_x;
	int	delta_y;
	int	sign_x;
	int	sign_y;
	int	i;

	delta_x = ft_abs(n1.x - n2.x);
	sign_x = n2.x - n1.x > 0 ? 1 : -1;
	delta_y = ft_abs(n1.y - n2.y);
	sign_y = n2.y - n1.y > 0 ? 1 : -1;
	i = 0;
	ft_putpixel(f, n1.x, n1.y, n1.argb);
	if (delta_y == 0 || delta_x >= delta_y)
		while (++i <= delta_x)
			ft_putpixel(f, n1.x + sign_x * i, sign_x * i * (n2.y - n1.y) /
	(n2.x - n1.x) + n1.y, ft_aprox_color(n1, n2, (double)i / (double)delta_x));
	else if (delta_x == 0 || delta_x < delta_y)
	{
		i = 0;
		while (++i <= delta_y)
			ft_putpixel(f, sign_y * i * (n2.x - n1.x) / (n2.y - n1.y) + n1.x,
	n1.y + sign_y * i, ft_aprox_color(n1, n2, (double)i / (double)delta_y));
	}
}

void		ft_putwire(t_fdf *f, t_wire *w)
{
	int		y;
	int		x;

	ft_putpixel(f, w->nods[0][0].x, w->nods[0][0].y, w->nods[0][0].argb);
	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			if (x + 1 < w->x_range)
				ft_putline(f, w->nods[y][x], w->nods[y][x + 1]);
			if (y + 1 < w->y_range)
				ft_putline(f, w->nods[y][x], w->nods[y + 1][x]);
		}
	}
}
