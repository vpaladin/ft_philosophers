#include "philosophers.h"

int	error(char *str)
{
	ft_putstr(str);
	return (0);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != 0)
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_atoi(char *str)
{
	int		res;

	res = 0;
	if (*str == '+')
		str++;
	while (*str != 0)
	{
		if (*str >= '0' && *str <= '9')
		{
			res = (res * 10) + (*str - '0');
			if (res > 2147483647)
				return (-1);
			str++;
		}
		else
			return (-1);
	}
	return (res);
}
