#include "libft.h"

void	ft_doublefree(char **s)
{
	int		i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
