/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:33:06 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/20 02:41:58 by ahaloui          ###   ########.fr       */
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

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
	pthread_mutex_t	death;
	pthread_mutex_t	var;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				state;
	int				last_meal_time;
	int				eat_count;
	int				start_time;
	int				dead_philo;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	print;
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

// utils2.c
int		check_death(t_philo *philo);
int		gettime(void);
void	my_printf(t_philo *philo, char *str);
int		my_usleep(int time);
void	add_to_table(t_philo **philos);

// utils3.c
void	philosopher_thread(t_philo *philo);
void	print_philo(t_philo *philos);
void	help_create_threads(t_philo *philos);

#endif