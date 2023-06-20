/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 01:14:46 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/20 02:26:34 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	print_philo(t_philo *philos)
{
	printf("id: %d\n", philos->id);
	printf("num_of_philo: %d\n", philos->data->num_of_philo);
	printf("time_to_die: %d\n", philos->data->time_to_die);
	printf("time_to_eat: %d\n", philos->data->time_to_eat);
	printf("time_to_sleep: %d\n", philos->data->time_to_sleep);
	printf("dead_philo: %d\n", philos->dead_philo);
	printf("num_of_times_each_philo_must_eat: %d\n",
		philos->data->num_of_times_each_philo_must_eat);
}

void	help_create_threads(t_philo *philos)
{
	int	j;

	j = 0;
	while (j < philos->data->num_of_philo)
	{
		pthread_create(&philos->thread, NULL,
			(void *)philosopher_thread, philos);
		philos = philos->next;
		j++;
	}
}
