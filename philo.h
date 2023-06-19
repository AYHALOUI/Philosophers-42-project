/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:33:06 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/19 00:56:43 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

enum e_state
{
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time;
	int	time_to_sleep;
	int	num_of_times_each_philo_must_eat;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				state;
	int				last_meal_time;
	int				eat_count;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	var;
	pthread_mutex_t	forks;
	struct s_philo	*next;
}	t_philo;

// utils.c
void	quit(void);
int		is_white_space(char c);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
void	check_if_valid_args(int ac, char **av);

// utils1.c
void	init_data(t_data *data, int ac, char **av);
void	init_philos(t_philo *philo, t_data *data);
void	print_data(t_data *data);
void	print_philos(t_philo *philo);
t_philo	*ft_lstnew(t_philo *philo, int id, t_philo *tmp);
void	ft_lstadd_back(t_philo **alst, t_philo *new);

#endif