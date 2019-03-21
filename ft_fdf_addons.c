#include "fdf.h"

int	ft_atoi_base_positiv(const char *s, int base)
{
	int	res;
	int	i;

	if (s == NULL || base < 2 || base > 16 )
		return (ft_error_print("atoi error 1\n", -1));
	res = 0;
	i = -1;
	while (++i < ft_strlen(s))
	{
		if (s[i] < '0' || s[i] > 'f' || (s[i] > '9' && s[i] < 'A') || (s[i] > 'F' && s[i] < 'a'))
			return (ft_error_print("atoi error 2\n", -1));
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

	if ((ukz = malloc(sizeof(void*) * (y + 1))) == NULL)
		return (NULL);
	ft_bzero(ukz, y + 1);
	i = 0;
	while(i < y)
	{
		if ((ukz[i] = malloc(size * (x + 1))) == NULL)
			return (NULL);
		ft_bzero(ukz[i], y + 1);
		i++;
	}
	return (ukz);
}

int		ft_error_print(char *s, int i)
{
	ft_printf("%s", s);
	return (i);
}
