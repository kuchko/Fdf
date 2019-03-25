#include "fdf.h"

int ft_keys(int key, void *param)
{
	if (key == 53)
		exit(0);
//	ft_printf("%d \n", key);
	return(0);
}

void	ft_putpixel(t_fdf *f, int x, int y, int color)
{
	int *i;

	if (x > -1 && x < f->win_width && y > -1 && y < f->win_high)
	{
		i = (int*)f->adr;
		i[y * f->img_width + x] = color;
	}
}

int	ft_draw(t_wire *w, t_fdf *f)
{
	f->mlx_ptr = mlx_init();
	f->win_ptr = mlx_new_window(f->mlx_ptr, f->win_width, f->win_high, "FDF");
	f->img_ptr = mlx_new_image(f->mlx_ptr, f->win_width, f->win_high);
	f->adr = mlx_get_data_addr(f->img_ptr, &f->bpp, &f->size_line, &f->endian);
	ft_putwire(f, w);
	ft_printf("z_arnge = %d\nz_min = %d\nz_max = %d\n", w->z_range, w->z_min, w->z_max);



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


	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img_ptr, 0, 0);
	mlx_key_hook(f->win_ptr, ft_keys, (void*)0);
	mlx_loop(f->mlx_ptr);
	return (0);
}

void	ft_putline(t_fdf *f, t_nod n1, t_nod n2)
{
	int delta_x;
	int delta_y;
	int sign_x;
	int sign_y;
	int i;

	delta_x = ft_abs(n1.x - n2.x);
	sign_x = n2.x - n1.x > 0 ? 1 : -1;
	delta_y = ft_abs(n1.y - n2.y);
	sign_y = n2.y - n1.y > 0 ? 1 : -1;
	i = 0;
	ft_putpixel(f, n1.x, n1.y, n1.argb);
	if (delta_y == 0 || delta_x >= delta_y)
		while(++i <= delta_x)
			ft_putpixel(f, n1.x + sign_x * i, sign_x * i * (n2.y - n1.y)/(n2.x - n1.x) + n1.y, n1.argb);
	else if (delta_x == 0 || delta_x < delta_y)
	{
		i = 0;
		while(++i <= delta_y)
			ft_putpixel(f, sign_y * i * (n2.x - n1.x)/(n2.y - n1.y) + n1.x, n1.y + sign_y * i , n1.argb);
	}
}

void	ft_putwire(t_fdf *f, t_wire *w)
{
	int y;
	int x;

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

