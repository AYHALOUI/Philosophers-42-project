/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:56:17 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/24 21:42:03 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_dinging_data(t_dinging_data *data, int ac, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start_time = my_gettime();
	data->flag = 0;
	pthread_mutex_init(&data->last_meal_mutex, NULL);
	pthread_mutex_init(&data->start_time_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	if (ac == 6)
		data->num_of_times_each_philo_must_eat = ft_atoi(av[5]);
	else
		data->num_of_times_each_philo_must_eat = 0;
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
	new->last_meal_time = my_gettime();
	new->next = tmp;
	return (new);
}
