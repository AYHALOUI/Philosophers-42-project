/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 01:09:56 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/20 03:02:10 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_to_table(t_philo **philos)
{
	t_philo	*tmp;
	int		i;

	i = 1;
	*philos = ft_lstnew(*philos, i, NULL);
	tmp = *philos;
	while (i < tmp->data->num_of_philo)
	{
		tmp->next = ft_lstnew(tmp, ++i, tmp->next);
		tmp = tmp->next;
	}
	tmp->next = *philos;
}

int	check_death(t_philo *philo)
{
	int	i;
	if (gettime() - philo->last_meal_time >= philo->data->time_to_die)
	{
		i = 0;
		pthread_mutex_lock(&philo->data->death);
		while (i < philo->data->num_of_philo)
		{
			philo->dead_philo = 1;
			philo = philo->next;
			i++;
		}
		pthread_mutex_unlock(&philo->data->death);
		my_printf(philo, "died");
		return (1);
	}
	else
	{
		// pthread_mutex_unlock(&philo->data->death);
		return (0);
	}
}

// int check_death(t_philo* philo)
// {
//     pthread_mutex_lock(&philo->data->death); // Acquire the mutex to synchronize access to shared data

//     unsigned long long current_time = gettime();
//     int time_since_last_meal = current_time - philo->last_meal_time;

//     pthread_mutex_unlock(&philo->data->death); // Release the mutex after accessing shared data

//     if (time_since_last_meal >= philo->data->time_to_die)
//         return 1; // Philosopher has died
//     else
//         return 0; // Philosopher is still alive
// }
int	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_printf(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->print);
	printf("%d %d %s\n", gettime() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->print);
}

int	my_usleep(int time)
{
	int	start;

	start = gettime();
	while (gettime() - start < time)
		usleep(100);
	return (1);
}
