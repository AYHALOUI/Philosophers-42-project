/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 03:12:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/07/19 16:20:54 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_thread(t_philo *philo)
{
	if (philo->philo_number % 2 == 0)
		usleep(600);
	pthread_mutex_lock(&philo->data->last_meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->last_meal_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		doing_something(philo, "has taken a fork", KNRM);
		pthread_mutex_lock(&philo->next->fork_mutex);
		doing_something(philo, "has taken a fork", KBLU);
		doing_something(philo, "is eating", KYEL);
		pthread_mutex_lock(&philo->data->last_meal_mutex);
		philo->last_meal_time = get_current_time();
		philo->eat_count++;
		if (philo->eat_count == philo->data->num_of_times_each_philo_must_eat)
			philo->data->flag++;
		pthread_mutex_unlock(&philo->data->last_meal_mutex);
		wait_to_do(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo->next->fork_mutex);
		doing_something(philo, "is sleeping", KGRN);
		wait_to_do(philo->data->time_to_sleep);
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
		if (get_current_time()
			- philos->last_meal_time >= philos->data->time_to_die)
		{
			pthread_mutex_lock(&philos->data->print_mutex);
			printf("%d %d died\n", get_current_time()
				- philos->data->start_time, philos->philo_number);
			philos->data->dead = 1;
			usleep(50);
			return ;
		}
		else if (philos->data->flag == philos->data->num_of_philo)
			return ;
		philos = philos->next;
		pthread_mutex_unlock(&philos->data->last_meal_mutex);
		usleep(200);
	}
}
