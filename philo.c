/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:24:33 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/27 15:48:31 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo, char flag)
{
	if (*philo->death)
	{
		if (flag == 'e')
		{
			pthread_mutex_unlock(philo->fork_left);
			pthread_mutex_unlock(philo->fork_right);
		}
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	long long	eat_start;
	long long	wait_time;

	print_manager(philo, 'e');
	pthread_mutex_lock(&philo->time_manage);
	eat_start = philo->last_meal;
	pthread_mutex_unlock(&philo->time_manage);
	wait_time = (long long)philo->time_to_eat;
	if (smart_sleep(philo, eat_start, 'e', wait_time))
		return (1);
	if (philo->num_of_eat > 0)
	{
		philo->meal_count++;
		pthread_mutex_lock(philo->access_data);
		*philo->total_eat = *philo->total_eat + 1;
		pthread_mutex_unlock(philo->access_data);
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	long long	sleep_start;
	long long	wait_time;

	print_manager(philo, 's');
	sleep_start = current_time_is();
	wait_time = (long long)philo->time_to_sleep;
	if (smart_sleep(philo, sleep_start, 's', wait_time))
		return (1);
	return (0);
}

int	thinking(t_philo *philo)
{
	long long	next_eat;
	long long	time_to_think;
	long long	last_meal;
	long long	think_start;

	print_manager(philo, 't');
	pthread_mutex_lock(&philo->time_manage);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->time_manage);
	think_start = current_time_is();
	next_eat = last_meal + (philo->time_to_eat * 3);
	time_to_think = (long long)philo->time_to_eat * 2
		- (long long)philo->time_to_sleep;
	if (next_eat > current_time_is())
	{
		usleep((time_to_think * 0.7) * 1000);
		if (smart_sleep(philo, think_start, 't', time_to_think * 0.9))
			return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->access_data);
	pthread_mutex_unlock(philo->access_data);
	if (philo->num_of_philo == 1)
		return (solo_philo(philo), NULL);
	else if (philo->num_of_philo % 2 == 0)
		even_philo(philo);
	else
		odd_philo(philo);
	return (NULL);
}
