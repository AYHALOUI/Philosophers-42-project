/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:56:17 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/19 00:48:06 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	init_data(t_data *data, int ac, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time = 0;
	if (ac == 6)
		data->num_of_times_each_philo_must_eat = ft_atoi(av[5]);
	else
		data->num_of_times_each_philo_must_eat = 0;
}


// void	print_data(t_data *data)
// {
// 	printf("num_of_philo: %d\n", data->num_of_philo);
// 	printf("time_to_die: %d\n", data->time_to_die);
// 	printf("time_to_eat: %d\n", data->time_to_eat);
// 	printf("time_to_sleep: %d\n", data->time_to_sleep);
// 	printf("num_of_times_each_philo_must_eat: %d\n",
// 		data->num_of_times_each_philo_must_eat);
// }

void	init_philos(t_philo *philo, t_data *data)
{
	philo->id = 0;
	philo->state = 0;
	philo->data = data;
}

void	print_philos(t_philo *philo)
{
	printf("id: %d\n", philo->id);
	printf("state: %d\n", philo->state);
	// print_data(philo->data);
}

t_philo	*ft_lstnew(t_philo *philo, int id, t_philo *tmp)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->state = philo->state;
	new->data = philo->data;
	new->next = tmp;
	pthread_mutex_init(&new->forks, NULL);
	return (new);
}

void	ft_lstadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
		last = last->next;
	last->next = new;
}

