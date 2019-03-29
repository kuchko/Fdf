#include "fdf.h"

int	ft_atoi_base_positiv(const char *s, int base)
{
	int		res;
	size_t	i;

	if (s == NULL || s[0] == '\0' || base < 2 || base > 16)
		return (-1);
	res = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] < '0' || s[i] > 'f' || (s[i] > '9' && s[i] < 'A') || (s[i] > 'F' && s[i] < 'a'))
			return (-1);
		if (s[i] >= '0' && s[i] <= '9')
			res = res * base + s[i] - '0';
		if (s[i] >= 'A' && s[i] <= 'F')
			res = res * base + s[i] - 'A' + 10;
		if (s[i] >= 'a' && s[i] <= 'f')
			res = res * base + s[i] - 'a' + 10;
		i++;
	}
	return (res);
}

int		ft_fdf_atoi(char *str, int *r)
{
	int				i;
	unsigned long	res;
	int				sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (str[i] < '0' || str[i] > '9')
		return(0);
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		if (i > 10)
			return (0);
		res = 10 * res + str[i++] - 48;
	}
	if (res >= 1073741823)
		return (0);
	*r = sign * (int)res;
	return (i);
}

void	**ft_double_malloc(size_t size, size_t y, size_t x)
{
	void	**ukz;
	size_t		i;

	if ((ukz = malloc(sizeof(void*) * (y))) == NULL)
		return (NULL);
	i = 0;
	while(i < y)
	{
		if ((ukz[i] = malloc(size * (x))) == NULL)
			return (NULL);
		i++;
	}
	return (ukz);
}

void	ft_error(char *s)
{
	ft_printf("%s", s);
	system("leaks fdf > leaks");
	exit(0);
}
