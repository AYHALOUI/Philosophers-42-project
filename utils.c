#include "philo.h"

void quit()
{
    write(2, "Error\n", 6);
    exit(1);
}

static int	is_white_space(char c)
{
	if ((c >= '\t' && c <= '\r' ) || c == ' ' )
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	unsigned int		i;
	int					signe;
	unsigned long int	result;

	i = 0;
	result = 0;
	signe = 1;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			quit();
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	if ((result > 2147483648 && signe == -1)
		|| (result > 2147483647 && signe == 1))
		quit();
	return (result * signe);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void check_if_valid_args(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    while (i < ac)
    {
        j = 0;
        while(av[i][j])
        {
            if (!ft_isdigit(av[i][j]))
                quit();
            j++;
        }
        i++;
    }
}