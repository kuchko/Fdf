#include "fdf.h"

static int	ft_x(void *p)
{
	(void)p;
	system("leaks fdf > leaks");
	exit(0);
	return (0);
}

static void	ft_draw_menu(t_fdf *f)
{
	mlx_string_put(f->mlx_ptr, f->win_ptr, 740, 100, 0xff0000, "WELCOME to FDF project by okuchko");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 750, 250, 0x00ffff, "please, press any key to start:");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 300, 0xffd700, "1                         parallel up view");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 325, 0xffd700, "2                           isometric view");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 350, 0xffd700, "3                         perspective view");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 400, 0xffd700, "q                          original colors");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 425, 0xffd700, "w                          gradient colors");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 450, 0xffd700, "e                    fill with green color");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 500, 0xffd700, "left arrow                       move left");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 525, 0xffd700, "right arrow                     move right");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 550, 0xffd700, "up arrow                           move up");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 575, 0xffd700, "down arrow                       move down");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 625, 0xffd700, "+                                zoom plus");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 650, 0xffd700, "-                               zoom minus");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 700, 0xffd700, "num 1                      turn by oZ left");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 725, 0xffd700, "num 3                     turn by oZ right");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 750, 0xffd700, "num 2                        turn by oX up");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 775, 0xffd700, "num 5                      turn by oX down");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 800, 0xffd700, "num 4                      turn by oY left");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 700, 825, 0xffd700, "num 6                     turn by oY right");
}

int			ft_draw(t_fdf *f)
{

	f->mlx_ptr = mlx_init();
	f->win_ptr = mlx_new_window(f->mlx_ptr, f->win_width, f->win_high, "FDF");
	f->img_ptr = mlx_new_image(f->mlx_ptr, f->win_width, f->win_high);
	f->adr = mlx_get_data_addr(f->img_ptr, &f->bpp, &f->size_line, &f->endian);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img_ptr, 0, 0);
	mlx_destroy_image(f->mlx_ptr,f->img_ptr);
	ft_draw_menu(f);
	mlx_hook(f->win_ptr, 17, 0, ft_x, f);
	mlx_hook(f->win_ptr, 2, 0, ft_keys, f);
	mlx_loop(f->mlx_ptr);
	return (0);
}

void		ft_re_draw(t_fdf *f)
{
	t_wire	*w;

	f->img_ptr = mlx_new_image(f->mlx_ptr, f->win_width, f->win_high);
	w = f->w[f->wire_mod];
	ft_copy_wire(&f->w_orig, w);
	if (w->color_mod == 1)
		ft_color_by_z(w);
	if (w->color_mod == 2)
		ft_color_fill(w, 0x7cfc00);
	ft_zoom_wire(w);
	if (w->angle.x != 0.0 || w->angle.y != 0.0 || w->angle.z != 0.0)
		ft_rotate_wire(w, &w->angle);
	if (f->wire_mod == 2)
		ft_iso_wire(w);
	if (f->wire_mod == 3)
		ft_perspective_wire(w);
	ft_move_wire(w);
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
