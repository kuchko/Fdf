#include "fdf.h"

static int	ft_valid_symbols(t_list *lst, int y_range)
{
	int		i;
	int		j;

	i = 0;
	while (lst)
	{
		j = 0;
		while (((char*)lst->content)[j])
			if (ft_strchr("-+,0xX123456789ABCDEFabcdef ",
								 ((char*)lst->content)[j++]) == NULL)
				return (0);
		lst = lst->next;
		i++;
	}
	if (i == y_range)
		return (1);
	return(0);
}


static int	ft_read_to_list(t_list **start, int fd)
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
	i > 0 ? free(l) : 0;
	return (i);
}

void	ft_read(t_wire *wire, t_list **start, int argc, char **argv)
{
	int		fd;

	*start = NULL;
	if (argc == 1)
		ft_error("usage:	fdf map_file\n");
	if (argc > 2)
		ft_error("fdf must have only one map_file\n");
	if ((fd = open(argv[1], O_DIRECTORY)) > 0)
		ft_error("open directory is invalid\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error("open map_file error\n");
	if ((wire->y_range = ft_read_to_list(start, fd)) == 0)
		ft_error("invalid file content\n");
	close(fd);
	if (wire->y_range > 10000)
		ft_error("map is too big\n");
	if(ft_valid_symbols(*start, wire->y_range) == 0)
		ft_error("invalid symbols in file\n");
	if (!ft_make_valid_wire(*start, wire))
		ft_error("map error. coordinates might be out of range.\n");
}




