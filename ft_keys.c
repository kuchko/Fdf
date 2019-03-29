#include "fdf.h"

static void ft_iso_change(int key, t_wire *w)
{
	if (key == 87)
		w->angle.x -= M_PI_2 * 0.02;
	else if (key == 84)
		w->angle.x += M_PI_2 * 0.02;
	else if (key == 88)
		w->angle.y += M_PI_2 * 0.02;
	else if (key == 86)
		w->angle.y -= M_PI_2 * 0.02;
	else if (key == 85)
		w->angle.z += M_PI_2 * 0.02;
	else if (key == 83)
		w->angle.z -= M_PI_2 * 0.02;
}

static void	ft_zoom_change(int key, t_wire *w)
{
	if (key == 78 && w->zoom >= 0.1)
		w->zoom -= 0.1;
//		w->zoom *= 0.95;
	else if (key == 69 && w->zoom < 10.0)
//		w->zoom *= 1.1;
		w->zoom += 0.1;
}

static void	ft_bias_change(int key, t_wire *w)
{
	if (key == 123)
		w->x_bias -= 10;
	else if (key == 124)
		w->x_bias += 10;
	else if (key == 125)
		w->y_bias += 10;
	else if (key == 126)
		w->y_bias -= 10;
}

static int		ft_keys_continue(int key, t_fdf *f)
{
	if (key == 78 || key == 69)
	{
		ft_zoom_change(key, f->w[f->wire_mod]);
		ft_re_draw(f);
	}
	else if (key >= 123 || key <= 126)
	{
		ft_bias_change(key, f->w[f->wire_mod]);
		ft_re_draw(f);
	}
	return (0);
}

int				ft_keys(int key, t_fdf *f)
{
	if (key == 53)
	{
		system("leaks fdf > leaks");
		exit(0);
	}
	else if (key == 18 || key == 19 || key == 20)
	{
		f->wire_mod = key - 17;
		ft_re_draw(f);
	}
	else if (key == 12 || key == 13 || key == 14)
	{
		f->w[f->wire_mod]->color_mod = key - 12;
		ft_re_draw(f);
	}
	else if (key >= 83 && key <= 88)
	{
		ft_iso_change(key, f->w[f->wire_mod]);
		ft_re_draw(f);
	}
	else
		ft_keys_continue(key, f);
	return(0);
}









	// {
	// 	f->img_ptr = mlx_new_image(f->mlx_ptr, f->win_width, f->win_high);
	// 	ft_putwire(f, &f->w_up);
	// }
	// else if (key == 18 )
	// {
	// 	f->img_ptr = mlx_new_image(f->mlx_ptr, f->win_width, f->win_high);
	// 	ft_putwire(f, &f->w_up);
	// }
	// else if (key == 19)
	// {
	// 	f->img_ptr = mlx_new_image(f->mlx_ptr, f->win_width, f->win_high);
	// 	ft_putwire(f, &f->w_iso);
	// }
	// if (key == 91)
	// 	ft_axis_plus
	// 	exit(0);
	//ft_printf("%d \n", key);
