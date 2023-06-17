// # include "utils.c"
# include "philo.h"


int main(int ac, char **av) {
    
    int i;
    t_info *info;
    t_philo *philo;
    if (ac != 5 && ac != 6)
        quit();
    check_if_valid_args(ac, av);
    i = 1;
    while (i < ac)
    {
        printf("%s\n", av[i]);
        i++;
    }
    init_info(&info, &philo, ac, av);
    create_table(&info, &philo, ac, av);
    return 0;
}






