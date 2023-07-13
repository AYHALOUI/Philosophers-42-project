/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:56:17 by ahaloui           #+#    #+#             */
/*   Updated: 2023/07/12 10:07:00 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_dinging_data(t_dinging_data *data, int ac, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	if (!data->num_of_philo)
		return (printf("At least one philo\n"), -1);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (!data->time_to_die || !data->time_to_eat || !data->time_to_sleep)
		return (-1);
	data->start_time = get_current_time();
	data->flag = 0;
	if (ac == 6)
	{
		data->num_of_times_each_philo_must_eat = ft_atoi(av[5]);
		if (!data->num_of_times_each_philo_must_eat)
		{
			printf("the Input is 0, the philo will not eat\n");
			return (-1);
		}
	}
	else
		data->num_of_times_each_philo_must_eat = 0;
	pthread_mutex_init(&data->last_meal_mutex, NULL);
	pthread_mutex_init(&data->start_time_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (0);
}

t_philo	*ft_lstnew(t_philo *philo, int id, t_philo *tmp, t_dinging_data *data)
{
	t_philo	*new;

	(void)philo;
	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->philo_number = id;
	new->data = data;
	new->last_meal_time = get_current_time();
	new->next = tmp;
	return (new);
}
