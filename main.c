/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:44:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/20 02:42:20 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	philosopher_thread(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->start_time = gettime();
	while (1)
	{
		pthread_mutex_lock(&philo->forks);
		if (!philo->dead_philo)
			my_printf(philo, "has taken a right fork");
		pthread_mutex_lock(&philo->next->forks);
		if (!philo->dead_philo)
		{
			my_printf(philo, "has taken a left fork");
			my_printf(philo, "is eating");
		}
		my_usleep(philo->data->time_to_eat);
		pthread_mutex_lock(&philo->data->var);
		philo->last_meal_time = gettime();
		pthread_mutex_unlock(&philo->data->var);
		pthread_mutex_unlock(&philo->forks);
		pthread_mutex_unlock(&philo->next->forks);
		if (!philo->dead_philo)
			my_printf(philo, "is sleeping");
		my_usleep(philo->data->time_to_sleep);
		if (!philo->dead_philo)
			my_printf(philo, "is thinking");
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	*data;

	data = malloc(sizeof(t_data));
	philos = NULL;
	check_if_valid_args(ac, av);
	pthread_mutex_init(&data->var, NULL);
	pthread_mutex_init(&data->death, NULL);
	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	init_data(data, ac, av);
	philos = malloc(sizeof(t_philo) * data->num_of_philo);
	philos->data = data;
	add_to_table(&philos);
	help_create_threads(philos);

	// *******************************************************************
	// while (i < data->num_of_philo)
	// {
	// 	print_philo(philos);
	// 	printf("_______________________________________________\n");
	// 	philos = philos->next;
	// 	i++;
	// }
	// *******************************************************************

	while (1)
	{
		pthread_mutex_lock(&philos->data->var);
		if (check_death(philos))
			break ;
		pthread_mutex_unlock(&philos->data->var);
		if (philos->next != NULL)
			philos = philos->next;
	}
	pthread_mutex_destroy(&philos->data->var);
	pthread_mutex_destroy(&philos->data->death);
	return (0);
}
