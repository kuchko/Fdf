#include "fdf.h"
#include <stdio.h>

int	ft_make_valid_wire(t_list *lst, t_wire *w)
{
	if ((w->x_range = ft_get_x_range(lst)) == 0)
		return (0);
	if (w->x_range > 10000)
		ft_error("map is too big\n");
	if (!(w->nods = (t_nod**)ft_double_malloc(sizeof(t_nod), w->y_range, w->x_range)))
		ft_error("double_malloc error\n");
	if (!(ft_wire_write(lst, w)))
		return (0);
	if (ft_get_z_range(w) < 0)
		ft_error("z_range error\n");
//		return (ft_error_print("ft_wire_write out = 0\n",0));
	return (1);
}

int	ft_wire_write(t_list *lst, t_wire *w)
{
	char **c;
	int i;
	int j;

	j = -1;
	while (lst && (++j + 1))
	{
		if (ft_get_x_range(lst) != w->x_range || (c = ft_strsplit(lst->content, ' ')) == NULL)
			return (0);
		i = -1;
		while(c[++i])
		{
			w->nods[j][i].y = j;
			w->nods[j][i].x = i;
			w->nods[j][i].z = ft_atoi(c[i]);
			if ((w->nods[j][i].argb = ft_get_argb(c[i])) < 0)
			{
				ft_doublefree(c);
				return (0);
			}
		}
		lst = lst->next;
		ft_doublefree(c);
	}
	return (1);
}

int ft_get_argb(char *c)
{
	int u;
	char *l;

	u = ft_count_char(c, ',');
	if (u == 0)
		return (0xFFFFFF);
	if (u > 1)
		return (-1);
	l = ft_strchr(c, ',') + 1;
	if (ft_strchr("xX", l[1]) == NULL || *ft_strchr("xX", l[1]) == '\0')
		ft_printf("is NULL\n");
	if (l[0] != '0' || ft_strlen(l) > 8)
	{
		ft_printf("invalid color\n");
		return (-1);
	}
	u = ft_atoi_base_positiv(l + 2, 16);
	return (u);
}



int	ft_get_x_range(t_list *lst)
{
	char	**c;
	int		i;

	i = 0;
	if ((c = ft_strsplit(lst->content, ' ')) == NULL)
		return (0);
	while(c[i])
		i++;
	ft_doublefree(c);
	return (i);
}

int		ft_get_z_range(t_wire *w)
{
	int y;
	int x;

	y = -1;
	w->z_min = 0;
	w->z_max = 0;
	while (++y < w->y_range)
	{
		x = -1;
		while (++x < w->x_range)
		{
			w->z_min = w->nods[y][x].z < w->z_min ? w->nods[y][x].z : w->z_min;
			w->z_max = w->nods[y][x].z > w->z_max ? w->nods[y][x].z : w->z_max;
		}
	}
	return (w->z_range = ft_abs(w->z_min) + ft_abs(w->z_max));
}

// int	ft_wire_malloc(t_wire *w)
// {
// 	int i;

// 	if ((w->nods = (t_nod**)malloc(sizeof(t_nod*) * (w->y_range + 1))) == NULL)
// 		return (0);
// 	i = 0;
// 	while(i < w->y_range)
// 	{
// 		if ((w->nods[i] = (t_nod*)malloc(sizeof(t_nod) * (w->x_range + 1))) == NULL)
// 			return (0);
// 		i++;
// 	}
// 	w->nods[i] = NULL;
// 	return (1);
// }
