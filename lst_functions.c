# include "philo.h"

void	ft_lstadd_back(t_info **info, t_info *new)
{
	t_info	*tmp;

	if (info)
	{
		if (*info == NULL)
		{
			*info = new;
			new = NULL;
		}
		else
		{
			tmp = *info;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
			tmp = NULL;
			new = NULL;
		}
	}
}

t_info    *ft_lstnew(t_philo *philo)
{
    t_info	*new;

    new = (t_info *)malloc(sizeof(t_info));
    if (new == NULL)
        return (NULL);
    new->philo = philo;
    new->next = NULL;
    return (new);
}

void create_table(t_info **info, t_philo *philo, int ac, char **av)
{
    int i;
    t_info *tmp;

    i = 0;
    while (i < philo->num_of_philo)
    {
        tmp = ft_lstnew(philo);
        ft_lstadd_back(info, tmp);
        i++;
    }
}
// int	ft_lstsize(t_info *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		i++;
// 		lst = lst->next;
// 	}
// 	return (i);
// }