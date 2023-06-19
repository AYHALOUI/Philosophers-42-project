/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:44:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/19 00:58:37 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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

void	print_philo(t_philo *philos)
{
	printf("id: %d\n", philos->id);
	printf("num_of_philo: %d\n", philos->data->num_of_philo);
	printf("time_to_die: %d\n", philos->data->time_to_die);
	printf("time_to_eat: %d\n", philos->data->time_to_eat);
	printf("time_to_sleep: %d\n", philos->data->time_to_sleep);
	printf("num_of_times_each_philo_must_eat: %d\n", philos->data->num_of_times_each_philo_must_eat);
}


// void	log_state(t_philo	*philo, enum e_state state)
// {
// 	long long	timestamp;
// 	char		log_message[100];

// 	timestamp = get_time();
// 	if (state == EAT)
// 		sprintf(log_message, "%lld %d is eating\n", timestamp, philo->id);
// 	else if (state == SLEEP)
// 		sprintf(log_message, "%lld %d is sleeping\n", timestamp, philo->id);
// 	else if (state == THINK)
// 		sprintf(log_message, "%lld %d is thinking\n", timestamp, philo->id);
// 	else if (state == DIE)
// 		sprintf(log_message, "%lld %d died\n", timestamp, philo->id);
// }



void	philosopher_thread(t_philo *philo)
{
	int		start_time;

	if (philo->id % 2 == 0)
		usleep(1000);
	start_time = gettime();
	while (1)
	{
		pthread_mutex_lock(&philo->forks);
		printf("time %d id %d has taken a r fork\n",
			gettime() - start_time, philo->id);
		pthread_mutex_lock(&philo->next->forks);
		printf("time %d id %d has taken a l fork\n",
			gettime() - start_time, philo->id);
		printf("time %d id %d is eating\n", gettime() - start_time, philo->id);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->forks);
		pthread_mutex_unlock(&philo->next->forks);
		printf("time %d id %d is sleeping\n", gettime() - start_time, philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		printf("time %d id %d is thinking\n", gettime() - start_time, philo->id);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	*data;

	data = malloc(sizeof(t_data));
	philos = NULL;
	check_if_valid_args(ac, av);
	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	init_data(data, ac, av);
	philos = malloc(sizeof(t_philo) * data->num_of_philo);
	philos->data = data;
	add_to_table(&philos);

	// while (i < data->num_of_philo)
	// {
	// 	print_philo(philos);
	// 	printf("_______________________________________________\n");
	// 	philos = philos->next;
	// 	i++;
	// }

	int j = 0;
	while (j < data->num_of_philo)
	{
		pthread_create(&philos->thread, NULL, (void *)philosopher_thread, philos);
		philos = philos->next;
		j++;
	}
	while(1);
	return (0);
}
