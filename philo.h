# ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

enum e_state
{
    EAT,
    SLEEP,
    THINK
};

typedef struct s_philo
{
    int id;
    int state;
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_of_times_each_philo_must_eat;
} t_philo;

typedef struct s_info
{
    t_philo *philo;
    struct s_info *next;
} t_info;

void init_philo(t_philo *philo, int ac, char **av);
void init_info(t_info *info, t_philo *philo, int ac, char **av);
void	ft_lstadd_back(t_info **info, t_info *new);
// lst functions
void	ft_lstadd_back(t_info **info, t_info *new);
t_info    *ft_lstnew(t_philo *philo);
// int     ft_lstsize(t_info *info);
void    create_table(t_info **info, t_philo **philo, int ac, char **av);

int ft_atoi(char *str);
void check_if_valid_args(int ac, char **av);
int is_digit(char *c);
void quit();
# endif