#include "philo.h"

int input_check(int ac, char **av)
{
    int i;
    int num;

    i = 1;
    while(i < ac)
    {
        num = ft_atoi(av[i]);
        if(num < 1)
            return 1;
        i++;
    }
    return 0;
}

void free_all(t_data *data)
{
    if(data->fork)
        free(data->fork);
    if(data->philo)
        free(data->philo);
    if(data)
        free(data);
}