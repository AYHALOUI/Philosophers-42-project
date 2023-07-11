/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:30:59 by ahaloui           #+#    #+#             */
/*   Updated: 2023/07/11 13:05:48 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return (-1);
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	if ((result > 2147483648 && signe == -1)
		|| (result > 2147483647 && signe == 1))
		return (-1);
	return (result * signe);
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9') || c == '+');
}

int	check_if_valid_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]) || ft_atoi(av[i]) == -1
				)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
