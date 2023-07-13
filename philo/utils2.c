/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 01:09:56 by ahaloui           #+#    #+#             */
/*   Updated: 2023/07/12 10:06:00 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_to_table(t_philo **philos, t_dinging_data *data)
{
	t_philo	*tmp;
	int		i;

	i = 1;
	*philos = ft_lstnew(*philos, i, NULL, data);
	tmp = *philos;
	pthread_mutex_init(&tmp->fork_mutex, NULL);
	while (i < tmp->data->num_of_philo)
	{
		tmp->next = ft_lstnew(tmp, ++i, tmp->next, data);
		tmp = tmp->next;
		pthread_mutex_init(&tmp->fork_mutex, NULL);
	}
	tmp->next = *philos;
}

int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	doing_something(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%s%d %d %s%s\n", color, get_current_time() - philo->data->start_time,
		philo->philo_number, str, END);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	wait_to_do(int time_to_wait)
{
	int	time_of_begin;

	time_of_begin = get_current_time();
	while (get_current_time() - time_of_begin < time_to_wait)
		usleep(100);
	return (1);
}
