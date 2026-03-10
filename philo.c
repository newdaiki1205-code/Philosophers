/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:24:33 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/10 19:09:30 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo, char flag)
{
	pthread_mutex_lock(&philo->data->death_check);
	if (philo->data->death)
	{
		pthread_mutex_unlock(&philo->data->death_check);
		if (flag == 'e')
		{
			pthread_mutex_unlock(philo->fork_first);
			pthread_mutex_unlock(philo->fork_second);
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_check);
	return (0);
}

int	eating(t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&philo->time_manage);
	philo->last_meal = current_time_is();
	print_is_eating(philo);
	pthread_mutex_unlock(&philo->time_manage);
	current_time = current_time_is();
	while (current_time - philo->last_meal < philo->time_to_eat)
	{
		if (death_check(philo, 'e'))
			return (1);
		current_time = current_time_is();
		usleep(5);
	}
	if (philo->num_of_eat > 0)
	{
		pthread_mutex_lock(&philo->lock_meal_count);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->lock_meal_count);
		pthread_mutex_lock(&philo->data->eat_count);
		philo->data->total_eat++;
		pthread_mutex_unlock(&philo->data->eat_count);
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	long long	ct;
	long long	ss;

	print_is_sleeping(philo);
	ss = current_time_is();
	ct = current_time_is();
	while (ct - ss < philo->time_to_sleep)
	{
		if (death_check(philo, 's'))
			return (1);
		ct = current_time_is();
		usleep(5);
	}
	return (0);
}

void	solo_philo(t_philo *philo)
{
	long long	current_time;

	print_taken_fork(philo);
	current_time = current_time_is();
	while (current_time - philo->start_time < philo->time_to_die)
		current_time = current_time_is();
	pthread_mutex_lock(&philo->data->death_check);
	philo->data->death = 1;
	pthread_mutex_unlock(&philo->data->death_check);
	print_died(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philo == 1)
		return (solo_philo(philo), NULL);
	while (1)
	{
		pthread_mutex_lock(philo->fork_first);
		print_taken_fork(philo);
		pthread_mutex_lock(philo->fork_second);
		print_taken_fork(philo);
		if (eating(philo))
			return (NULL);
		// if (death_check(philo, 'e'))
		// 	return (NULL);
		if (philo->meal_count == philo->num_of_eat)
		{
			pthread_mutex_unlock(philo->fork_first);
			pthread_mutex_unlock(philo->fork_second);
			return (NULL);
		}
		pthread_mutex_unlock(philo->fork_first);
		pthread_mutex_unlock(philo->fork_second);
		if (sleeping(philo))
			return (NULL);
		// if (death_check(philo, 's'))
		// 	return (NULL);
		print_is_thinking(philo);
	}
}
