/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:44:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/22 01:05:48 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_thread(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(600);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal_time = gettime();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		my_printf(philo, "has taken a right fork", KNRM);
		pthread_mutex_lock(&philo->next->fork_mutex);
		my_printf(philo, "has taken a left fork", KBLU);
		my_printf(philo, "is eating", KYEL);
		pthread_mutex_lock(&philo->data->last_meal_mutex);
		philo->last_meal_time = gettime();
		philo->eat_count++;
		if (philo->eat_count == philo->data->num_of_times_each_philo_must_eat)
			philo->data->flag++;
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
		my_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo->next->fork_mutex);
		my_printf(philo, "is sleeping", KGRN);
		my_usleep(philo->data->time_to_sleep);
		my_printf(philo, "is thinking", KBLU);
	}
}


void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_destroy(&philo->fork_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->data->last_meal_mutex);
	pthread_mutex_destroy(&philo->data->start_time_mutex);
	pthread_mutex_destroy(&philo->data->print_mutex);
}

void monitor_threads(t_philo *philos)
{
	while (1)
	{
		pthread_mutex_lock(&philos->data->last_meal_mutex);
		if (gettime() - philos->last_meal_time >= philos->data->time_to_die)
		{
			my_printf(philos, "died", KRED);
			pthread_mutex_lock(&philos->data->print_mutex);
			destroy_mutex(philos);
			return ;
		}
		else if (philos->data->flag == philos->data->num_of_philo)
		{
			pthread_mutex_lock(&philos->data->print_mutex);
			printf("%sall philosophers have eaten %d times%s\n", KRED, philos->data->num_of_times_each_philo_must_eat, END);
			destroy_mutex(philos);
			return ;
		}
		philos = philos->next;
		pthread_mutex_unlock(&philos->data->last_meal_mutex);
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	*data;

	data = malloc(sizeof(t_data));
	philos = NULL;
	if (check_if_valid_args(ac, av))
		return (0);
	init_data(data, ac, av);
	add_to_table(&philos, data);
	help_create_threads(philos);
	monitor_threads(philos);
	return (0);
}
