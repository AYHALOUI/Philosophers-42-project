/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:44:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/21 17:11:04 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_thread(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(600);
	pthread_mutex_lock(&philo->data->var);
	philo->start_time = gettime();
	pthread_mutex_unlock(&philo->data->var);
	pthread_mutex_lock(&philo->last);
	philo->last_meal_time = gettime();
	pthread_mutex_unlock(&philo->last);
	while (1)
	{
		pthread_mutex_lock(&philo->forks);
		my_printf(philo, "has taken a right fork");
		pthread_mutex_lock(&philo->next->forks);
		my_printf(philo, "has taken a left fork");
		my_printf(philo, "is eating");
		pthread_mutex_lock(&philo->last);
		philo->last_meal_time = gettime();
		pthread_mutex_unlock(&philo->last);
		my_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->forks);
		pthread_mutex_unlock(&philo->next->forks);
		my_printf(philo, "is sleeping");
		my_usleep(philo->data->time_to_sleep);
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
	pthread_mutex_init(&data->print, NULL);
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
	// t_philo *tmp = philos;
	while (1)
	{
		pthread_mutex_lock(&philos->last);
		usleep(200);
		if (gettime() - philos->last_meal_time >= philos->data->time_to_die)
		{
			my_printf(philos, "died");
			pthread_mutex_unlock(&philos->last);
			pthread_mutex_lock(&philos->data->print);
			break ;
		}
		pthread_mutex_unlock(&philos->last);
		philos = philos->next;
	}
	// int i = 0;
	// while (i < tmp->data->num_of_philo)
	// {
	// 	pthread_mutex_destroy(&tmp->last);
	// 	pthread_mutex_destroy(&tmp->forks);
	// 	tmp = tmp->next;
	// 	i++;
	// }
	// pthread_mutex_destroy(&philos->data->var);
	// pthread_mutex_destroy(&philos->data->death);
	// pthread_mutex_destroy(&philos->data->print);
	return (0);
}
