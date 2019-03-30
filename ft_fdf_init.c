#include "fdf.h"

void	ft_fdf_init(t_fdf *f)
{
	f->win_width = 1600;
	f->win_high = 1000;
	f->img_width = 1600;
	f->img_high = 1000;
	f->wire_mod = 1;
	ft_fit_wire(f, &f->w_orig);
	ft_get_z_range(&f->w_orig);
	f->w_orig.x_bias = f->win_width / 2;
	f->w_orig.y_bias = f->win_high / 2;
	f->w_orig.angle.x = M_PI_2 * 0.0;
	f->w_orig.angle.y = M_PI_2 * 0.0;
	f->w_orig.angle.z = M_PI_2 * 0.0;
	f->w_orig.zoom = 1.0;
	f->w_orig.color_mod = 0;
	if (!(ft_wires_malloc(f)))
		ft_error("malloc error in wires\n");
	ft_copy_params(&f->w_orig, &f->w_up);
	ft_copy_params(&f->w_orig, &f->w_iso);
	ft_copy_params(&f->w_orig, &f->w_parral);
	ft_copy_wire(&f->w_orig, &f->w_up);
	ft_copy_wire(&f->w_orig, &f->w_iso);
	ft_copy_wire(&f->w_orig, &f->w_parral);
}

void	ft_copy_params(t_wire *w1, t_wire *w2)
{
	w2->x_range = w1->x_range;
	w2->y_range = w1->y_range;
	w2->z_range = w1->z_range;
	w2->z_min = w1->z_min;
	w2->z_max = w1->z_max;
	w2->dx = w1->dx;
	w2->dy = w1->dy;
	w2->x_bias = w1->x_bias;
	w2->y_bias = w1->y_bias;
	w2->angle.x = w1->angle.x;
	w2->angle.y = w1->angle.y;
	w2->angle.z = w1->angle.z;
	w2->zoom = w1->zoom;
	w2->color_mod = w1->color_mod;
}

int		ft_wires_malloc(t_fdf *f)
{
	if (!(f->w_up.nods = (t_nod**)ft_double_malloc(sizeof(t_nod),
			f->w_orig.y_range, f->w_orig.x_range)))
		return (0);
	if (!(f->w_iso.nods = (t_nod**)ft_double_malloc(sizeof(t_nod),
			f->w_orig.y_range, f->w_orig.x_range)))
		return (0);
	if (!(f->w_parral.nods = (t_nod**)ft_double_malloc(sizeof(t_nod),
			f->w_orig.y_range, f->w_orig.x_range)))
		return (0);
	if (!(f->w = (t_wire**)malloc(sizeof(t_wire*) * 4)))
		return (0);
	f->w[0] = &f->w_orig;
	f->w[1] = &f->w_up;
	f->w[2] = &f->w_iso;
	f->w[3] = &f->w_parral;
	return (1);
}

void	ft_fit_wire(t_fdf *f, t_wire *w)
{
	double	del;
	int		y;
	int		x;
	int		dz_mul;
	int		dz_div;

	del = w->x_range > w->y_range ? w->x_range : w->y_range;
	w->dx = del < (f->img_width / 2) ? f->img_width / 2 / del : 1;
	w->dy = w->dx;
	dz_mul = w->z_range < f->img_high / 5 ? (f->img_high / 5) / w->z_range : 1;
	dz_div = w->z_range > f->img_high ? 2 * w->z_range / f->img_high : 1;
	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			w->nods[y][x].x = w->nods[y][x].x * w->dx - w->dx *
										(w->x_range - 1) / 2;
			w->nods[y][x].y = w->nods[y][x].y * w->dy - w->dy *
										(w->y_range - 1) / 2;
			w->nods[y][x].z = (w->nods[y][x].z * dz_mul) / dz_div;
		}
	}
}

void	ft_copy_wire(t_wire *w1, t_wire *w2)
{
	int y;
	int x;

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
}
