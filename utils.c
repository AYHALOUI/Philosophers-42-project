/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:30:59 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/22 00:27:21 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	quit(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	is_white_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
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

int	check_if_valid_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	} 
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
