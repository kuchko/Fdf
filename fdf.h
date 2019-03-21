
#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"

# define FD1 0

typedef struct	s_fdf_nod
{
	int			x; //?
	int			y; //?
	int			z;
	int			argb;
}				t_nod;

typedef struct	s_original_wire
{
	t_nod		**nods;
	int			x_range;
	int			y_range;
	int			dx;
	int			dy;
	int			dz;
}				t_wire;






int		ft_read_to_list(t_list **start, int fd);
int		ft_valid_symbols(t_list *lst, int y_max);
int		ft_make_valid_wire(t_list *lst, t_wire *w);
int		ft_wire_malloc(t_wire *w);
int		ft_get_x_range(t_list *lst);

#endif
