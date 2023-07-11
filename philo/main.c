/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:44:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/24 21:43:47 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo **philos)
{
	int		i;
	int		len;
	t_philo	*tmp;

	i = 0;
	tmp = *philos;
	len = (*philos)->data->num_of_philo;
	while (i < len)
	{
		tmp = *philos;
		*philos = (*philos)->next;
		free(tmp);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			*philos;
	t_dinging_data	*data;
	int				check;

	philos = NULL;
	check = check_if_valid_args(ac, av);
	if (check)
	{	
		if (check == -1)
			printf("Error: wrong argument\n");
		else
			printf("Error: wrong number of arguments\n");
		return (0);
	}
	data = malloc(sizeof(t_dinging_data));
	if (!data)
		return (0);
	init_dinging_data(data, ac, av);
	add_to_table(&philos, data);
	help_create_threads(philos);
	monitor_threads(philos);
	destroy_mutex(philos);
	free_philos(&philos);
	free(data);
	return (0);
}
