#include "philo.h"

int death_check(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_check);
    if(philo->data->death)
    {
        pthread_mutex_unlock(&philo->data->death_check);
        return 1;
    }
    pthread_mutex_unlock(&philo->data->death_check);
    return 0;
}

int eating(t_philo *philo)
{
    struct timeval current_time;
    long long milisecond;

    pthread_mutex_lock(&philo->time_manage);
    gettimeofday(&current_time, NULL);
    milisecond = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    philo->last_meal = milisecond;
    print_is_eating(philo);
    pthread_mutex_unlock(&philo->time_manage);
    gettimeofday(&current_time, NULL);
    milisecond = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    while(milisecond - philo->last_meal < philo->time_to_eat)
    {
        if(death_check(philo))
        {
            pthread_mutex_unlock(philo->fork_first);
            pthread_mutex_unlock(philo->fork_second);
            return 1;
        }
        gettimeofday(&current_time, NULL);
        milisecond = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
        usleep(5);
    }
    if(philo->num_of_eat > 0)
    {
        pthread_mutex_lock(&philo->lock_meal_count);
        philo->meal_count++;
        pthread_mutex_unlock(&philo->lock_meal_count);
        pthread_mutex_lock(&philo->data->eat_count);
        philo->data->total_eat++;
        pthread_mutex_unlock(&philo->data->eat_count);
    }
    return 0;
}

int sleeping(t_philo *philo)
{
    struct timeval current_time;
    long long ct;
    struct timeval sleep_start;
    long long ss;
    
    print_is_sleeping(philo);
    gettimeofday(&sleep_start, NULL);
    ss = (long long)sleep_start.tv_sec * 1000 + (sleep_start.tv_usec / 1000);
    gettimeofday(&current_time, NULL);
    ct = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    while(ct - ss < philo->time_to_sleep)
    {
        if(death_check(philo))
            return 1;
        gettimeofday(&current_time, NULL);
        ct = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
        usleep(5);
    }
    return 0;
}

void solo_philo(t_philo *philo)
{
    struct timeval current_time;
    long long miliseconds;
    
    print_taken_fork(philo);
    gettimeofday(&current_time, NULL);
    miliseconds = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    while(miliseconds - philo->start_time < philo->time_to_die)
    {
        gettimeofday(&current_time, NULL);
        miliseconds = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    }
    pthread_mutex_lock(&philo->data->death_check);
    philo->data->death = 1;
    pthread_mutex_unlock(&philo->data->death_check);
    print_died(philo);
}

void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo*)arg;
    if(philo->data->num_of_philo == 1)
    {
        solo_philo(philo);
        return NULL;
    }
    while(1)
    {
        pthread_mutex_lock(philo->fork_first);
        print_taken_fork(philo);
        pthread_mutex_lock(philo->fork_second);
        print_taken_fork(philo);
        if(eating(philo))
        {
            pthread_mutex_unlock(philo->fork_first);
            pthread_mutex_unlock(philo->fork_second);
            return NULL;
        }
        if(philo->meal_count == philo->num_of_eat)
        {
            pthread_mutex_unlock(philo->fork_first);
            pthread_mutex_unlock(philo->fork_second);
            return NULL;
        }
        pthread_mutex_unlock(philo->fork_first);
        pthread_mutex_unlock(philo->fork_second);
        if(sleeping(philo))
            return NULL;
        print_is_thinking(philo);
    }
}
