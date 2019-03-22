#include "fdf.h"

int	ft_atoi_base_positiv(const char *s, int base)
{
	int	res;
	int	i;

	if (s == NULL || base < 2 || base > 16 )
		return (-1);
	res = 0;
	i = -1;
	while (++i < ft_strlen(s))
	{
		if (s[i] < '0' || s[i] > 'f' || (s[i] > '9' && s[i] < 'A') || (s[i] > 'F' && s[i] < 'a'))
			return (-1);
		if (s[i] >= '0' && s[i] <= '9')
			res = res * base + s[i] - '0';
		if (s[i] >= 'A' && s[i] <= 'F')
			res = res * base + s[i] - 'A' + 10;
		if (s[i] >= 'a' && s[i] <= 'f')
			res = res * base + s[i] - 'a' + 10;
	}
	return (res);
}

void	**ft_double_malloc(size_t size, size_t y, size_t x)
{
	void	**ukz;
	int		i;

	if ((ukz = malloc(sizeof(void*) * (y))) == NULL)
		return (NULL);
	ft_bzero(ukz, y);
	i = 0;
	while(i < y)
	{
		if ((ukz[i] = malloc(size * (x))) == NULL)
			return (NULL);
		ft_bzero(ukz[i], y);
		i++;
	}
	return (ukz);
}

void	ft_error(char *s)
{
	ft_printf("%s", s);
	exit(0);
}
