#include "fdf.h"

void	ft_color_by_z(t_wire *w)
{
	int y;
	int x;
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
				w->nods[y][x].argb = ft_aprox_color(n2, n1, (double) w->nods[y][x].z / (double) w->z_min);
			if (w->nods[y][x].z == 0)
				w->nods[y][x].argb = n2.argb;
			if (w->nods[y][x].z > 0 && w->z_max != 0)
				w->nods[y][x].argb = ft_aprox_color(n2, n3, (double) w->nods[y][x].z / (double) w->z_max);
		}
	}
}

void	ft_color_fill(t_wire *w, int color)
{
	int y;
	int x;

	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
			w->nods[y][x].argb = color;
	}
}

void	ft_move_and_zoom_wire(t_wire *w)
{
	int y;
	int x;

	y = -1;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			w->nods[y][x].x = w->nods[y][x].x * w->zoom + w->x_bias;
			w->nods[y][x].y = w->nods[y][x].y * w->zoom + w->y_bias;
		}
	}
}

// void	ft_move_wire(t_wire *w, int y_m, int x_m)
// {
// 	int y;
// 	int x;

// 	y = -1;
// 	while (++y < w->y_range)
// 	{
// 		x = -1;
// 		while (++x < w->x_range)
// 		{
// 			w->nods[y][x].x += x_m;
// 			w->nods[y][x].y += y_m;
// 		}
// 	}
// }

void	ft_rotate_wire(t_wire *w2, t_iso *iso)
{
	int y;
	int x;
	int	pre;

	y = -1;
	while (++y < w2->y_range)
	{
		x = -1;
		while (++x < w2->x_range)
		{
			if (iso->x != 0.0)
			{
				pre = w2->nods[y][x].y;
				w2->nods[y][x].y = w2->nods[y][x].y * cos(iso->x) + w2->nods[y][x].z * sin(iso->x);
				w2->nods[y][x].z = - pre * sin(iso->x) + w2->nods[y][x].z * cos(iso->x);
			}
			if (iso->y != 0.0)
			{
				pre = w2->nods[y][x].x;
				w2->nods[y][x].x = w2->nods[y][x].x * cos(iso->y) + w2->nods[y][x].z * sin(iso->y);
				w2->nods[y][x].z = - pre * sin(iso->y) + w2->nods[y][x].z * cos(iso->y);
			}
			if (iso->z != 0.0)
			{
				pre = w2->nods[y][x].x;
				w2->nods[y][x].x = w2->nods[y][x].x * cos(iso->z) - w2->nods[y][x].y * sin(iso->z);
				w2->nods[y][x].y = pre * sin(iso->z) + w2->nods[y][x].y * cos(iso->z);
			}
		}
	}
}

void	ft_iso_wire(t_wire *w1)
{
	int y;
	int x;
	int y_pre;
	int x_pre;

	y = -1;
	while (++y < w1->y_range)
	{
		x = -1;
		while (++x < w1->x_range)
		{
			x_pre = w1->nods[y][x].x;
			y_pre = w1->nods[y][x].y;
			w1->nods[y][x].x = (x_pre - y_pre) * cos(0.523599);
			w1->nods[y][x].y = (x_pre + y_pre) * sin(0.523599) - w1->nods[y][x].z;
		}
	}
}

void	ft_perspective_wire(t_wire *w1)
{
	int y;
	int x;
	double dist;
	// int y_pre;
	// int x_pre;

	dist = -600;
	y = -1;
	while (++y < w1->y_range)
	{
		x = -1;
		while (++x < w1->x_range)
		{
			// x_pre = w1->nods[y][x].x;
			// y_pre = w1->nods[y][x].y;
			if(w1->nods[y][x].z != dist)
			{
				w1->nods[y][x].x = w1->nods[y][x].x * dist / (w1->nods[y][x].z + dist);
				w1->nods[y][x].y = w1->nods[y][x].y * dist / (w1->nods[y][x].z + dist);
			}
		}
	}
}


// void	ft_iso_wire(t_wire *w1, t_wire *w2, t_iso *iso)
// {
// 	int y;
// 	int x;

// 	y = -1;
// 	while (++y < w1->y_range)
// 	{
// 		x = -1;
// 		while (++x < w1->x_range)
// 		{
// 			w2->nods[y][x].x = (w1->nods[y][x].x - w1->nods[y][x].y) * cos(0.523599);
// 			w2->nods[y][x].y = (w1->nods[y][x].x + w1->nods[y][x].y) * sin(0.523599) - w1->nods[y][x].z;
// 		}
// 	}
// }

// void	ft_recount_wire(t_wire *w)
// {
// 	int y;
// 	int x;

// 	y = -1;
// 	while (++y < w->y_range)
// 	{
// 		x = -1;
// 		while (++x < w->x_range)
// 		{
// 			w->nods[y][x].x += w->x_bias;
// 			w->nods[y][x].y += w->y_bias;
// 		}
// 	}
// }


// void	ft_rotate_wire(t_wire *w1, t_wire *w2, t_iso *iso)
// {
// 	int y;
// 	int x;

// 	y = -1;
// 	while (++y < w1->y_range)
// 	{
// 		x = -1;
// 		while (++x < w1->x_range)
// 		{
// 			w2->nods[y][x].x = (w1->nods[y][x].x - w1->nods[y][x].y) * cos(0.523599);
// 			w2->nods[y][x].y = (w1->nods[y][x].x + w1->nods[y][x].y) * sin(0.523599) - w1->nods[y][x].z;
// //			w2->nods[y][x].z = w1->nods[y][x].z;

// 			// if (iso->x != 0.0)
// 			// 	w2->nods[y][x].y = w1->nods[y][x].y * cos(iso->x) + w1->nods[y][x].z * sin(iso->x);
// 			// if (iso->x != 0.0)
// 			// 	w2->nods[y][x].z = - w1->nods[y][x].y * sin(iso->x) + w1->nods[y][x].z * cos(iso->x);
// 			// if (iso->y != 0.0)
// 			// 	w2->nods[y][x].x = w1->nods[y][x].x * cos(iso->y) + w1->nods[y][x].z * sin(iso->y);
// 			// if (iso->y != 0.0)
// 			// 	w2->nods[y][x].z = - w1->nods[y][x].x * sin(iso->y) + w1->nods[y][x].z * cos(iso->y);
// 			// if (iso->z != 0.0)
// 			// 	w2->nods[y][x].x = w1->nods[y][x].x * cos(iso->z) - w1->nods[y][x].y * sin(iso->z);
// 			// if (iso->z != 0.0)
// 			// 	w2->nods[y][x].y = w1->nods[y][x].x * sin(iso->z) + w1->nods[y][x].y * cos(iso->z);

// 			// w2->nods[y][x].y = w1->nods[y][x].y * cos(iso->x) + w1->nods[y][x].z * sin(iso->x) + w1->nods[y][x].x * sin(iso->z) + w1->nods[y][x].y * cos(iso->z);
// 			// w2->nods[y][x].z = - w1->nods[y][x].y * sin(iso->x) + w1->nods[y][x].z * cos(iso->x) - w1->nods[y][x].x * sin(iso->y) + w1->nods[y][x].z * cos(iso->y);
// 			// w2->nods[y][x].x = w1->nods[y][x].x * cos(iso->y) + w1->nods[y][x].z * sin(iso->y) + w1->nods[y][x].x * cos(iso->z) - w1->nods[y][x].y * sin(iso->z);

// 			// w2->nods[y][x].y = (w1->nods[y][x].y + w1->nods[y][x].y * cos(iso->x) + w1->nods[y][x].z * sin(iso->x) + w1->nods[y][x].x * sin(iso->z) + w1->nods[y][x].y * cos(iso->z))/1;
// 			// w2->nods[y][x].z = (w1->nods[y][x].z - w1->nods[y][x].y * sin(iso->x) + w1->nods[y][x].z * cos(iso->x) - w1->nods[y][x].x * sin(iso->y) + w1->nods[y][x].z * cos(iso->y))/1 ;
// 			// w2->nods[y][x].x = (w1->nods[y][x].x + w1->nods[y][x].x * cos(iso->y) + w1->nods[y][x].z * sin(iso->y) + w1->nods[y][x].x * cos(iso->z) - w1->nods[y][x].y * sin(iso->z)) /1;
// 		}
// 	}
// }
