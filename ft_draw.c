#include "fdf.h"

static int	ft_x(void *param)
{
	(void)param;
	system("leaks fdf > leaks");
	exit(0);
	return (0);
}

int	ft_draw(t_fdf *f)
{

	f->mlx_ptr = mlx_init();
	f->win_ptr = mlx_new_window(f->mlx_ptr, f->win_width, f->win_high, "FDF");
	f->img_ptr = mlx_new_image(f->mlx_ptr, f->win_width, f->win_high);

	f->adr = mlx_get_data_addr(f->img_ptr, &f->bpp, &f->size_line, &f->endian);
	//ft_re_draw(f);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img_ptr, 0, 0);
	mlx_destroy_image(f->mlx_ptr,f->img_ptr);

	// mlx_key_hook(f->win_ptr, ft_keys, f);
	mlx_hook(f->win_ptr, 17, 0, ft_x, f);
	mlx_hook(f->win_ptr, 2, 0, ft_keys, f);
	mlx_loop(f->mlx_ptr);
	return (0);
}



void	ft_re_draw(t_fdf *f)
{
	t_wire	*w;

	f->img_ptr = mlx_new_image(f->mlx_ptr, f->win_width, f->win_high);

	w = f->w[f->wire_mod];
	ft_copy_wire(&f->w_orig, w);
	if (w->color_mod == 1)
		ft_color_by_z(w);
	if (w->color_mod == 2)
		ft_color_fill(w, 0x7cfc00);
	// if (f->wire_mod == 2)
	// 	ft_iso_wire(w);
	if (w->angle.x != 0.0 || w->angle.y != 0.0 || w->angle.z != 0.0)
		ft_rotate_wire(w, &w->angle);
	if (f->wire_mod == 2)
		ft_iso_wire(w);
	if (f->wire_mod == 3)
		ft_perspective_wire(w);
	ft_move_and_zoom_wire(w);

	ft_putwire(f,w);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img_ptr, 0, 0);
	mlx_destroy_image(f->mlx_ptr,f->img_ptr);
}

























// void	ft_remake_wires(t_fdf	*f)
// {
// 	ft_copy_wire(&f->w_orig, &f->w_up);
// 	ft_recount_wire(&f->w_up);

// 	f->w_iso.angle.x = - M_PI_2 * 0;
// 	f->w_iso.angle.y = - M_PI_2 * 0;
// 	f->w_iso.angle.z = M_PI_2 * 0;
// 	ft_rotate_wire(&f->w_orig, &f->w_iso, &f->w_iso.angle);
// 	ft_recount_wire(&f->w_iso);

// }


//	ft_printf("z_arnge = %d\nz_min = %d\nz_max = %d\n", w->z_range, w->z_min, w->z_max);



// 	int i;
// 	int j;

// 	j = -1;
// 	while (++j < w->y_range)
// 	{
// 		i= -1;
// 		while (++i < w->x_range)
// //			mlx_pixel_put(f->mlx_ptr, f->win_ptr, 100 + 50 * w->nods[j][i].x, 100 + 50 * w->nods[j][i].y, w->nods[j][i].argb);
// 			ft_putpixel(f, 100 + 50 * w->nods[j][i].x, 100 + 50 * w->nods[j][i].y, w->nods[j][i].argb);

// 	}

// 	t_nod n1;
// 	n1.x = 100;
// 	n1.y = 100;
// 	n1.argb = 0xFFFFFF;
// 	t_nod n2;
// 	n2.x = 100;
// 	n2.y = 0;
// 	n2.argb = 0xFFFFFF;

// 	ft_putline(f, n1, n2);
