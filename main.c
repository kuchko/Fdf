// gcc -I minilibx testing.c -L minilibx -lmlx -framework OpenGL -framework AppKit
//man /Users/okuchko/Desktop/fdf/minilibx/man/man3/mlx.1
#include "fdf.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	int	fd;
	char *l;
	t_list *start;


	if (argc == 1 && ft_printf("usage:	fdf map_file\n"))
		return (0);
	if (argc > 2 && ft_printf("fdf must hace only one map_file\n"))
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) == -1 && ft_printf("open map_file error\n"))
		return (0);
	if ((start = ft_get_list(fd)) == NULL)
		return (0);

	t_list *tmp;

	tmp = start;
	while (tmp)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}

	close(fd);
	system("leaks fdf > leaks.txt");
	return(0);
}


t_list	*ft_get_list(int fd)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*start;
	char 	*l;
	int		i;

	i = 0;
	while (get_next_line(fd, &l) > 0 && ++i)
	{
		if (start == NULL)
		{
			if ((start = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (NULL);
			lst = start;
		}
		else
		{
			if ((tmp = ft_lstnew(l, ft_strlen(l) + 1)) == NULL)
				return (NULL);
			lst->next = tmp;
			lst = tmp;
		}
		free(l);
	}
	start->content_size = i;
	return (start);
}

/*
int deal_key(int key, void *param)
{
	if (key == 53)
		exit(0);
	ft_printf("%d \n", key);
	return(0);
}

int main()
{
	int i;

	void	*mlx_ptr;
	void	*win_ptr;

	i = -1;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 640, 480, "First window");
	while (++i < 100)
		mlx_pixel_put(mlx_ptr, win_ptr, 150 + i, 100 + i/2, 0xFFFFFF);
	mlx_string_put(mlx_ptr, win_ptr, 150, 100, 0xFFFFFF, "xXXx");
	mlx_key_hook(win_ptr, deal_key, (void*)0);
	mlx_loop(mlx_ptr);
	return (0);

}
*/
