#include "philo.h"

void are_you_alive(t_data *data)
{
    int i;
    struct timeval current_time;
    long long miliseconds;

    i = 0;
    while(1)
    {
        if(i == data->num_of_philo)
            i = 0;
        gettimeofday(&current_time, NULL);
        miliseconds = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
        usleep(1000);
        pthread_mutex_lock(&data->philo[i].time_manage);
        pthread_mutex_lock(&data->philo[i].lock_meal_count);
        pthread_mutex_lock(&data->eat_count);
        if((data->philo[i].meal_count != data->num_of_eat) && ((miliseconds - data->start_time) - (data->philo[i].last_meal - data->start_time) >= data->time_to_die))
        {
            pthread_mutex_lock(&data->death_check);
            data->death = 1;
            pthread_mutex_unlock(&data->death_check);
            print_died(&data->philo[i]);
            pthread_mutex_unlock(&data->philo[i].time_manage);
            pthread_mutex_unlock(&data->philo[i].lock_meal_count);
            pthread_mutex_unlock(&data->eat_count);
            return ;
        }
        pthread_mutex_unlock(&data->philo[i].time_manage);
        pthread_mutex_unlock(&data->philo[i].lock_meal_count);
        pthread_mutex_unlock(&data->eat_count);
        pthread_mutex_lock(&data->eat_count);
        if(data->num_of_eat > 0 && (data->total_eat == data->num_of_philo * data->num_of_eat))
        {
            pthread_mutex_unlock(&data->eat_count);
            return;
        }
        pthread_mutex_unlock(&data->eat_count);
        pthread_mutex_lock(&data->death_check);
        if(data->death)
        {
            pthread_mutex_unlock(&data->death_check);
            return;
        }
        pthread_mutex_unlock(&data->death_check);
        i++;
    }
}
