/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:44:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/18 02:54:47 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	add_to_table(t_philo *philos)
{
	int		i;
	t_philo	*tmp;

	i = 1;
	tmp = NULL;
	philos = ft_lstnew(philos, i, tmp);
	tmp = philos;
	i++;
	while (i <= philos->data->num_of_philo)
	{
		philos->next = ft_lstnew(philos, i, tmp);
		philos = philos->next; 
		i++;
	}
	philos = tmp;
	while (philos)
	{
		print_philos(philos);
		sleep(1);
		philos = philos->next;
	}
}


int	main(int ac, char **av)
{
	int		i;
	t_philo	*philos;
	t_philo	*tmp;
	t_data	*data;

	i = 1;
	data = malloc(sizeof(t_data));
	philos = NULL;
	tmp = NULL;
	check_if_valid_args(ac, av);
	if (ac == 5 || ac == 6)
	{
		init_data(data, ac, av);
		philos = malloc(sizeof(t_philo) * data->num_of_philo);
		init_philos(philos, data);
		add_to_table(philos);
	}
	return (0);
}	






