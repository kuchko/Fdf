#include "fdf.h"

int	ft_read_to_list(t_list **start, int fd)
{
	t_list	*lst;
	t_list	*tmp;
	char 	*l;
	int		i;

	i = 0;
	while (get_next_line(fd, &l) > 0 && ++i)
	{
		if (*start == NULL)
		{
			if ((*start = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (0);
			lst = *start;
		}
		else
		{
			if ((tmp = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (0);
			lst->next = tmp;
			lst = tmp;
		}
		free(l);
	}
	free(l);
	return (i);
}

int ft_valid_symbols(t_list *lst, int y_range)
{
	int		i;
	int		j;

	i = 0;
	while (lst)
	{
		j = 0;
		while (((char*)lst->content)[j])
			if (ft_strchr("-,0x123456789ABCDEFabcdef 	", ((char*)lst->content)[j++]) == NULL)
				return (0);
		lst = lst->next;
		i++;
	}
	if (i == y_range)
		return (1);
	return(0);
}
