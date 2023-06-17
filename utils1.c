#include "philo.h"

void init_philo(t_philo *philo, int ac, char **av)
{
    philo->num_of_philo = ft_atoi(av[1]);
    philo->time_to_die = ft_atoi(av[2]);
    philo->time_to_eat = ft_atoi(av[3]);
    philo->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        philo->num_of_times_each_philo_must_eat = ft_atoi(av[5]);
    else
        philo->num_of_times_each_philo_must_eat = -1;
}

void init_info(t_info *info, t_philo *philo, int ac, char **av)
{
    init_philo(philo, ac, av);
    info->philo = philo;
}