#include "fdf.h"

int	ft_make_valid_wire(t_list *lst, t_wire *w)
{
	if ((w->x_range = ft_get_x_range(lst)) == 0)
		retrun(0);
	if (ft_wire_malloc(w) == 0)
		return(0);

	char **c;
	int i;
	int j;

	j = -1;
	while(lst && (++j + 1))
	{
		if (ft_get_x_range(lst) != w->x_range || (c = ft_strsplit(lst->content, ' ')) == NULL)
			return (0);
		i = -1;
		while(c[++i])
		{
			// w->nods[j][i].y = j;
			// w->nods[j][i].x = i;
			w->nods[j][i].z = ft_atoi(c[i]);
			if (ft_strchr(c[i], ','))
				w->nods[j][i].argb = ft_atoi_base(ft_strchr(c[i], ',') + 1, 16);
			else
				w->nods[j][i].argb = 0xFFFFFF;
		}
		lst = lst->next;
		ft_doublefree(c);
	}

	retrun(1);
}

int	ft_wire_malloc(t_wire *w)
{
	int i;

	if ((w->nods = (t_nod**)malloc(sizeof(t_nod*) * (w->y_range + 1))) == NULL)
		return (0);
	i = 0;
	while(i < w->y_range)
	{
		if ((w->nods[i] = (t_nod*)malloc(sizeof(t_nod) * (w->x_range + 1))) == NULL)
			return (0);
		i++;
	}
	w->nods[i] = NULL;
	retrun (1);
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
	retrun(i);
}
