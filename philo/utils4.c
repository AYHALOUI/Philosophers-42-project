/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 03:12:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/07/11 15:22:59 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_thread(t_philo *philo)
{
	if (philo->philo_number % 2 == 0)
		usleep(600);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal_time = my_gettime();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		my_printf(philo, "has taken a fork", KNRM);
		pthread_mutex_lock(&philo->next->fork_mutex);
		my_printf(philo, "has taken a fork", KBLU);
		my_printf(philo, "is eating", KYEL);
		pthread_mutex_lock(&philo->data->last_meal_mutex);
		philo->last_meal_time = my_gettime();
		philo->eat_count++;
		if (philo->eat_count == philo->data->num_of_times_each_philo_must_eat)
			philo->data->flag++;
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
		my_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo->next->fork_mutex);
		my_printf(philo, "is sleeping", KGRN);
		my_usleep(philo->data->time_to_sleep);
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

void	monitor_threads(t_philo *philos)
{
	while (1)
	{
		pthread_mutex_lock(&philos->data->last_meal_mutex);
		if (my_gettime() - philos->last_meal_time >= philos->data->time_to_die)
		{
			my_printf(philos, "died", KRED);
			pthread_mutex_lock(&philos->data->print_mutex);
			destroy_mutex(philos);
			return ;
		}
		else if (philos->data->flag == philos->data->num_of_philo)
			return ;
		philos = philos->next;
		pthread_mutex_unlock(&philos->data->last_meal_mutex);
		usleep(200);
	}
}
