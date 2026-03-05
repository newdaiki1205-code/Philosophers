#include "philo.h"

int prep_thread (t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philo)
    {
        if(pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]))
            return 1;
        i++;
    }
    return 0;
}

int clean_thread(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philo)
    {
        if(pthread_join(data->philo[i].thread, NULL))
        {
            return 1;
        } 
        i++;
    }
    return 0;
}