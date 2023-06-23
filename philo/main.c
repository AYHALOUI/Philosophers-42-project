/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 01:44:43 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/23 00:36:47 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo **philos)
{
	t_philo	*head;
	t_philo	*tmp2;
	int		i;

	i = 0;
	head = *philos;
	while (head->next != *philos)
	{
		tmp2 = head;
		head = head->next;
		free(tmp2);
	}
	free(head);
}

void	print_list(t_philo *p)
{
	while (p != NULL)
	{
		printf("id = %d\n", p->id);
		p = p->next;
	}
}

void	ff()
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_data	*data;
	int		check;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	philos = NULL;
	check = check_if_valid_args(ac, av);
	if (check)
	{	
		if (check == -1)
			printf("Error: wrong argument\n");
		else
			printf("Error: wrong number of arguments\n");
		return (0);
	}
	init_data(data, ac, av);
	add_to_table(&philos, data);
	help_create_threads(philos);
	monitor_threads(philos);
	destroy_mutex(philos);
	free_philos(&philos);
	free(data);
	return (0);
}
