#include "fdf.h"

int			ft_get_x_range(t_list *lst)
{
	char	**c;
	int		i;

	i = 0;
	if ((c = ft_strsplit(lst->content, ' ')) == NULL)
		return (0);
	while (c[i])
		i++;
	ft_doublefree(c);
	return (i);
}

int			ft_get_z_range(t_wire *w)
{
	int		y;
	int		x;

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
	w->z_range = ft_abs(w->z_min) + ft_abs(w->z_max);
	return (w->z_range = w->z_range > 0 ? w->z_range : 1);
}

static int	ft_set_valid_nod(int j, int i, t_wire *w, char *c)
{
	int		k;
	int		m;

	k = 0;
	m = 0;
	if ((m = ft_fdf_atoi(c, &k)) == 0)
		return (0);
	w->nods[j][i].z = k;
	w->nods[j][i].argb = 0xFFFFFF;
	if (c[m] == '\0')
		return (1);
	if (c[m] == ',' && c[m + 1] == '0' && (c[m + 2] == 'x' || c[m + 2] == 'X')
				&& ft_strlen(&c[m + 3]) < 7 && !(ft_count_char(&c[m + 3], ',')))
	{
		w->nods[j][i].argb = ft_atoi_base_positiv(&c[m + 3], 16);
		if (w->nods[j][i].argb >= 0)
			return (1);
	}
	return (0);
}

static int	ft_wire_write(t_list *lst, t_wire *w)
{
	char	**c;
	int		i;
	int		j;

	j = -1;
	while (lst && (++j + 1))
	{
		if (ft_get_x_range(lst) != w->x_range ||
					(c = ft_strsplit(lst->content, ' ')) == NULL)
			return (0);
		i = -1;
		while (c[++i])
		{
			w->nods[j][i].y = j;
			w->nods[j][i].x = i;
			if (ft_set_valid_nod(j, i, w, c[i]) == 0)
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

int			ft_make_valid_wire(t_list *lst, t_wire *w)
{
	if ((w->x_range = ft_get_x_range(lst)) == 0)
		return (0);
	if (w->x_range > 10000)
		ft_error("map is too big\n");
	if (!(w->nods = (t_nod**)ft_double_malloc(sizeof(t_nod),
										w->y_range, w->x_range)))
		ft_error("double_malloc error\n");
	if (!(ft_wire_write(lst, w)))
		return (0);
	if (ft_get_z_range(w) < 0)
		ft_error("z_range error\n");
	return (1);
}
