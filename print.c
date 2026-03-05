#include "philo.h"

void print_taken_fork(t_philo *philo)
{
    struct timeval current_time;
    long long milisecond;
    
    if(death_check(philo))
            return ;
    gettimeofday(&current_time, NULL);
    milisecond = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d has taken a fork\n", milisecond - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}

void print_is_eating(t_philo *philo)
{
    if(death_check(philo))
            return ;
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d is eating\n", philo->last_meal - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}

void print_is_sleeping(t_philo *philo)
{
    struct timeval current_time;
    long long milisecond;
    
    if(death_check(philo))
            return ;
    gettimeofday(&current_time, NULL);
    milisecond = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d is sleeping\n", milisecond - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}

void print_is_thinking(t_philo *philo)
{
    struct timeval current_time;
    long long milisecond;
    
    if(death_check(philo))
            return ;
    gettimeofday(&current_time, NULL);
    milisecond = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d is thinking\n", milisecond - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}

void print_died(t_philo *philo)
{
    struct timeval current_time;
    long long milisecond;
    
    gettimeofday(&current_time, NULL);
    milisecond = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d died\n", milisecond - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}