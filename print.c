#include "philo.h"

void print_taken_fork(t_philo *philo)
{
    long long timestamp;
    
    if(death_check(philo, 'p'))
            return ;
    timestamp = current_time_is();
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d has taken a fork\n", timestamp - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}

void print_is_eating(t_philo *philo)
{
    if(death_check(philo, 'p'))
            return ;
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d is eating\n", philo->last_meal - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}

void print_is_sleeping(t_philo *philo)
{
    long long timestamp;
    
    if(death_check(philo, 'p'))
            return ;
    timestamp = current_time_is();
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d is sleeping\n", timestamp - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}

void print_is_thinking(t_philo *philo)
{
    long long timestamp;
    
    if(death_check(philo, 'p'))
            return ;
    timestamp = current_time_is(); 
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d is thinking\n", timestamp - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}

void print_died(t_philo *philo)
{
    long long timestamp;
    
    timestamp = current_time_is();
    pthread_mutex_lock(&philo->data->print);
    printf("%lld Philosopher %d died\n", timestamp - philo->start_time, philo->id + 1);
    pthread_mutex_unlock(&philo->data->print);
}