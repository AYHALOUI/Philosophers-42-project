/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:33:06 by ahaloui           #+#    #+#             */
/*   Updated: 2023/06/22 01:03:49 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

/*colors*/
#define KNRM  "\x1B[0m"
#define END   "\e[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
	int				start_time;
	int				flag;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	start_time_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_meal_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				last_meal_time;
	int				eat_count;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	
	struct s_philo	*next;
}	t_philo;

void	quit(void);
int		is_white_space(char c);
int		ft_atoi(char *str);
int		ft_isdigit(int c);
int		check_if_valid_args(int ac, char **av);
void	init_data(t_data *data, int ac, char **av);
t_philo	*ft_lstnew(t_philo *philo, int id, t_philo *tmp, t_data *data);
int		gettime(void);
void	my_printf(t_philo *philo, char *str, char *color);
int		my_usleep(int time);
void	add_to_table(t_philo **philos, t_data *data);
void	philosopher_thread(t_philo *philo);
void	print_philo(t_philo *philos);
void	help_create_threads(t_philo *philos);

#endif