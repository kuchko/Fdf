#include "fdf.h"

void	ft_fdf_init(t_fdf *f)
{
	f->win_width = 1600;
	f->win_high = 1000;
	f->img_width = 1600;
	f->img_high = 1000;
	f->w_cur = orig;
	ft_fit_wire(f, &f->w_orig);
	f->w_orig.z_range = ft_get_z_range(&f->w_orig);
	f->w_orig.x_bias = f->win_width / 2;
	f->w_orig.y_bias = f->win_high / 2;
	f->w_orig.angel.x = M_PI_2 * 0.0;
	f->w_orig.angel.y = M_PI_2 * 0.0;
	f->w_orig.angel.z = M_PI_2 * 0.0;
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
	w2->angel.x = w1->angel.x;
	w2->angel.y = w1->angel.y;
	w2->angel.z = w1->angel.z;
}

int ft_wires_malloc(t_fdf *f)
{
	if(!(f->w_up.nods = (t_nod**)ft_double_malloc(sizeof(t_nod), f->w_orig.y_range, f->w_orig.x_range)))
		return (0);
	if(!(f->w_iso.nods = (t_nod**)ft_double_malloc(sizeof(t_nod), f->w_orig.y_range, f->w_orig.x_range)))
		return (0);
	if(!(f->w_parral.nods = (t_nod**)ft_double_malloc(sizeof(t_nod), f->w_orig.y_range, f->w_orig.x_range)))
		return (0);
	return (1);
}


void	ft_fit_wire(t_fdf *f, t_wire *w)
{
	int del;
	int y;
	int x;
	int	dz_mult;
	int dz_div;

	del = w->x_range > w->y_range ? w->x_range : w->y_range;
//	ft_printf("w->x_range = %d, w->y_range = %d,  del = %d\n", w->x_range,w->y_range, del);
	w->dx = del < (f->img_width / 2) ? f->img_width / 2 / del : 1;
	w->dy = w->dx;
 	dz_mult = w->z_range < f->img_high / 6 ? (f->img_high / 6 )/ w->z_range : 1;
	dz_div = w->z_range > f->img_high ? w->z_range / f->img_high: 1;
//	ft_printf("w->dx = %d, w->dy = %d, dz_mult = %d, dz_div = %d\n", w->dx, w->dy, dz_mult, dz_div);
	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			w->nods[y][x].x = w->nods[y][x].x * w->dx - w->dx * w->x_range / 2;
			w->nods[y][x].y = w->nods[y][x].y * w->dy - w->dy * w->y_range / 2;
			w->nods[y][x].z = (w->nods[y][x].z * dz_mult) / dz_div;
		}
	}
}



void	ft_copy_wire(t_wire *w1, t_wire *w2)
{
	int y;
	int x;

	// w2->x_range = w1->x_range;
	// w2->y_range = w1->y_range;
	// w2->z_range = w1->z_range;
	// // w2->z_min = w1->z_min;
	// // w2->z_max = w1->z_max;
	// w2->dx = w1->dx;
	// w2->dy = w1->dy;
	// // w2->dz_div = w1->dz_div;
	// // w2->dz_mult = w1->dz_mult;
	// // if(!(w2->nods = (t_nod**)ft_double_malloc(sizeof(t_nod), w1->y_range, w1->x_range)))
	// // 	return (0);
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

void	ft_rotate_wire(t_wire *w1, t_wire *w2, t_iso *iso)
{
	int y;
	int x;

	y = -1;
	while (++y < w1->y_range)
	{
		x = -1;
		while (++x < w1->x_range)
		{
			// w2->nods[y][x].x = (w1->nods[y][x].x - w1->nods[y][x].y) * cos(0.523599);
			// w2->nods[y][x].y = (w1->nods[y][x].x + w1->nods[y][x].y) * sin(0.523599) - w1->nods[y][x].z;
			// w2->nods[y][x].z = w1->nods[y][x].z;

			// if (iso->x != 0.0)
			// 	w2->nods[y][x].y = w1->nods[y][x].y * cos(iso->x) + w1->nods[y][x].z * sin(iso->x);
			// if (iso->x != 0.0)
			// 	w2->nods[y][x].z = - w1->nods[y][x].y * sin(iso->x) + w1->nods[y][x].z * cos(iso->x);
			// if (iso->y != 0.0)
			// 	w2->nods[y][x].x = w1->nods[y][x].x * cos(iso->y) + w1->nods[y][x].z * sin(iso->y);
			// if (iso->y != 0.0)
			// 	w2->nods[y][x].z = - w1->nods[y][x].x * sin(iso->y) + w1->nods[y][x].z * cos(iso->y);
			// if (iso->z != 0.0)
			// 	w2->nods[y][x].x = w1->nods[y][x].x * cos(iso->z) - w1->nods[y][x].y * sin(iso->z);
			// if (iso->z != 0.0)
			// 	w2->nods[y][x].y = w1->nods[y][x].x * sin(iso->z) + w1->nods[y][x].y * cos(iso->z);

			// w2->nods[y][x].y = w1->nods[y][x].y * cos(iso->x) + w1->nods[y][x].z * sin(iso->x) + w1->nods[y][x].x * sin(iso->z) + w1->nods[y][x].y * cos(iso->z);
			// w2->nods[y][x].z = - w1->nods[y][x].y * sin(iso->x) + w1->nods[y][x].z * cos(iso->x) - w1->nods[y][x].x * sin(iso->y) + w1->nods[y][x].z * cos(iso->y);
			// w2->nods[y][x].x = w1->nods[y][x].x * cos(iso->y) + w1->nods[y][x].z * sin(iso->y) + w1->nods[y][x].x * cos(iso->z) - w1->nods[y][x].y * sin(iso->z);

			w2->nods[y][x].y = (w1->nods[y][x].y + w1->nods[y][x].y * cos(iso->x) + w1->nods[y][x].z * sin(iso->x) + w1->nods[y][x].x * sin(iso->z) + w1->nods[y][x].y * cos(iso->z))/1;
			w2->nods[y][x].z = (w1->nods[y][x].z - w1->nods[y][x].y * sin(iso->x) + w1->nods[y][x].z * cos(iso->x) - w1->nods[y][x].x * sin(iso->y) + w1->nods[y][x].z * cos(iso->y))/1 ;
			w2->nods[y][x].x = (w1->nods[y][x].x + w1->nods[y][x].x * cos(iso->y) + w1->nods[y][x].z * sin(iso->y) + w1->nods[y][x].x * cos(iso->z) - w1->nods[y][x].y * sin(iso->z)) /1;


		}
	}
}

void	ft_move_wire(t_wire *w, int y_m, int x_m)
{
	int y;
	int x;

	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			w->nods[y][x].x += x_m;
			w->nods[y][x].y += y_m;
		}
	}
}

void	ft_recount_wire(t_wire *w)
{
	int y;
	int x;

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

void	ft_remake_wires(t_fdf	*f)
{
	ft_copy_wire(&f->w_orig, &f->w_up);
	ft_recount_wire(&f->w_up);

	f->w_iso.angel.x = - M_PI_2 * 0;
	f->w_iso.angel.y = - M_PI_2 * 0;
	f->w_iso.angel.z = M_PI_2 * 0;
	ft_rotate_wire(&f->w_orig, &f->w_iso, &f->w_iso.angel);
	ft_recount_wire(&f->w_iso);

}
