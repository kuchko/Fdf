#include "fdf.h"

/*
void	ft_lstfree(t_list **alst)
{
	t_list	*nxt;

	if (*alst == NULL)
		return ;
	while (*alst)
	{
		ft_printf("free\n");
		nxt = (*alst)->next;
		free(*alst);
		free(&((*alst)->content_size));
		(*alst) = nxt;
	}
}
*/

void	ft_read(t_wire *wire, t_list **start, int argc, char **argv)
{
	int		fd;

	*start = NULL;
	if (argc == 1)// && ft_printf("usage:	fdf map_file\n"))
		ft_error("usage:	fdf map_file\n");
	if (argc > 2)// && ft_printf("fdf must have only one map_file\n"))
		ft_error("fdf must have only one map_file\n");
	if ((fd = open(argv[1], O_DIRECTORY)) > 0)// > 0 && ft_printf("open directory is invalid\n"))
		ft_error("open directory is invalid\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)// && ft_printf("open map_file error\n"))
		ft_error("open map_file error\n");
	if ((wire->y_range = ft_read_to_list(start, fd)) == 0)
		ft_error("invalid file content\n");
	ft_printf("read done\n");
	close(fd);
//	ft_show_list(start);
	if(ft_valid_symbols(*start, wire->y_range) == 0)
		ft_error("invalid symbols in file\n");
//	ft_printf("map_looks like valid\n");
//	ft_show_list(start);
	if (!ft_make_valid_wire(*start, wire))
		ft_error("map error\n");
//	ft_lstdel(&start, (free));
//	ft_lstfree(&start);
	ft_show_wire_coordinates(wire);
}



// void	ft_freelst(t_list **lst)
// {

// 	while (*lst)
// 	{
// 		free((*lst)->content);
// 	}
// }

int	ft_read_to_list(t_list **start, int fd)
{
	t_list	*lst;
	t_list	*tmp;
	char 	*l;
	int		i;

	i = 0;
	while (get_next_line(fd, &l) > 0 && ++i)
	{
//		ft_printf("reading.....\n");
		if (*start == NULL)
		{
			if ((*start = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (0);
			lst = *start;
//			ft_printf("aaaaa%s\n", lst->content);
		}
		else
		{
			if ((tmp = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (0);
			lst->next = tmp;
//			ft_printf("%s\n", lst->content);
			lst = tmp;
		}
		free(l);
	}
	i > 0 ? free(l) : 0;
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
			if (ft_strchr("-,0xX123456789ABCDEFabcdef ", ((char*)lst->content)[j++]) == NULL)
				return (0);
		lst = lst->next;
		i++;
	}
	if (i == y_range)
		return (1);
	return(0);
}
