
#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>

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
	int			z_range;
	int			z_min;
	int			z_max;
	int			dx;
	int			dy;
	int			dz_div;
	int			dz_mult;
}				t_wire;



void	ft_show_wire_coordinates(t_wire *w);

void	ft_read(t_wire *wire, t_list **start, int argc, char **argv);
// void	ft_read(t_wire *wire, int argc, char **argv);
int		ft_read_to_list(t_list **start, int fd);
int		ft_valid_symbols(t_list *lst, int y_max);

int		ft_make_valid_wire(t_list *lst, t_wire *w);
int		ft_wire_write(t_list *lst, t_wire *w);
int		ft_get_argb(char *c);
// int		ft_wire_malloc(t_wire *w);
int		ft_get_x_range(t_list *lst);
int		ft_get_z_range(t_wire *w);

int		ft_atoi_base_positiv(const char *s, int base);
void	**ft_double_malloc(size_t size, size_t y, size_t x);

int		ft_draw(t_wire *w, t_fdf *f);
void	ft_putline(t_fdf *f, t_nod n1, t_nod n2);
void	ft_putwire(t_fdf *f, t_wire *w);

void	ft_f_init(t_fdf *f);
void	ft_fit_wire(t_fdf *f, t_wire *w);
int		ft_copy_wire(t_wire *w1, t_wire *w2);

void	ft_error(char *s);
void	ft_show_list(t_list *lst);

#endif
