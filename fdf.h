
#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"

# define FD1 0

typedef struct	s_fdf
{
	char		**c;
	int			x;
	int			n;
	int			pl;
	int			sx;
	int			sy;
	char		*en;
	char		*fr;
}				t_fdf;

t_list	*ft_get_list(int fd);

#endif
